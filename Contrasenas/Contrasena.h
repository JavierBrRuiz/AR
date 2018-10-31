#ifndef CONTRASENA_H
#define CONTRASENA_H
class Contrasena{
    private:
    int length;
    char caracteres[];

    public:
    Contrasena();
    Contrasena(int _length);
    ~Contrasena();

    bool es_Contrasena(int _length);
    bool es_Fuerte();
    void cifrar_Contrasena();
    void descifrar_Contrasena();
    bool es_Correcta();
}
#endif
