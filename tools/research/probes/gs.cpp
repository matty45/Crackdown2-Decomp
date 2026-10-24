extern "C" int __cdecl sprintf(char *, const char *, ...);
void Consume(const char *s);

void GsProbe(const char *name)
{
    char buf[64];
    sprintf(buf, "%s", name);
    Consume(buf);
}

void __cdecl main(void) { GsProbe("x"); }
void Consume(const char *s) { (void)s; }
