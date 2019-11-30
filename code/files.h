FILE *openFile(const char *nom, const char *mode);
void closeFile(const char *nom, FILE * fd);

int readLine(FILE * sourceFile, char *sourceLine);
void writeLine(FILE * resultFile, char *resultLine);