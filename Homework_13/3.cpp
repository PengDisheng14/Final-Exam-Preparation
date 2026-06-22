#include <cstdio>
#include <cstdlib>
#include <iostream>

void AnnotationCancel(char *file1, char *file2)
{
    FILE *fin = fopen(file1, "r");
    if (!fin)
    {
        std::cerr << "无法打开源文件: " << file1 << std::endl;
        return;
    }

    FILE *fout = fopen(file2, "w");
    if (!fout)
    {
        std::cerr << "无法创建目标文件: " << file2 << std::endl;
        fclose(fin);
        return;
    }

    enum State
    {
        NORMAL,
        STRING,
        CHAR,
        LINE_COMMENT,
        BLOCK_COMMENT
    };
    State state = NORMAL;
    int ch, nextCh;

    while ((ch = fgetc(fin)) != EOF)
    {
        switch (state)
        {
        case NORMAL:
            if (ch == '"')
            {
                fputc(ch, fout);
                state = STRING;
            }
            else if (ch == '\'')
            {
                fputc(ch, fout);
                state = CHAR;
            }
            else if (ch == '/')
            {
                nextCh = fgetc(fin);
                if (nextCh == '/')
                {
                    state = LINE_COMMENT;
                }
                else if (nextCh == '*')
                {
                    state = BLOCK_COMMENT;
                }
                else
                {
                    fputc(ch, fout);
                    if (nextCh != EOF)
                    {
                        ungetc(nextCh, fin);
                    }
                }
            }
            else
            {
                fputc(ch, fout);
            }
            break;

        case STRING:
            fputc(ch, fout);
            if (ch == '"')
            {
                state = NORMAL;
            }
            else if (ch == '\\')
            {
                // 转义字符后的下一个字符原样输出且保持字符串状态
                nextCh = fgetc(fin);
                if (nextCh != EOF)
                {
                    fputc(nextCh, fout);
                }
            }
            break;

        case CHAR:
            fputc(ch, fout);
            if (ch == '\'')
            {
                state = NORMAL;
            }
            else if (ch == '\\')
            {
                nextCh = fgetc(fin);
                if (nextCh != EOF)
                {
                    fputc(nextCh, fout);
                }
            }
            break;

        case LINE_COMMENT:
            if (ch == '\n')
            {
                fputc(ch, fout); // 保留换行符，维持原行号
                state = NORMAL;
            }
            break;

        case BLOCK_COMMENT:
            if (ch == '*')
            {
                nextCh = fgetc(fin);
                if (nextCh == '/')
                {
                    state = NORMAL;
                }
                else
                {
                    ungetc(nextCh, fin);
                }
            }
            break;
        }
    }

    fclose(fin);
    fclose(fout);
}

int main()
{
    char input[] = "test.cpp";
    char output[] = "clean.cpp";
    AnnotationCancel(input, output);
    return 0;
}