#include <stdio.h>
#include <stdlib.h>

// Función para calcular el máximo común divisor
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Función para calcular exponenciación modular
// Esencial para RSA porque permite manejar grandes exponentes y módulos sin desbordamiento.
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            // Multiplica el resultado por la base cuando el exponente es impar
            result = (result * base) % mod;
        }
        // Cuadra la base y divide el exponente por 2
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Función para generar las claves pública y privada
// Se eligen dos números primos para crear las claves.
void generateKeys(long long *e, long long *d, long long *n) {
    // Primos pequeños para ejemplo; en la práctica, deben ser grandes
    long long p = 61, q = 53;
    // n es el módulo para las claves pública y privada
    *n = p * q;
    // Función totiente de Euler
    long long phi = (p - 1) * (q - 1);
    // e debe ser coprimo con phi y menor que phi
    *e = 2;
    while (gcd(*e, phi) != 1)
        (*e)++;
    *d = 1;
    // d es el inverso multiplicativo de e modulo phi
    while ((*d * *e) % phi != 1)
        (*d)++;
}

// Función para cifrar un carácter
long long encryptChar(char c, long long e, long long n) {
    return modPow(c, e, n);
}

// Función para descifrar un carácter
char decryptChar(long long c, long long d, long long n) {
    return (char)modPow(c, d, n);
}

int main() {
    long long e, d, n;
    // Genera las claves
    generateKeys(&e, &d, &n);

    char str[] = "SOMOS EL EQUIPO 9";
    // Longitud de la cadena sin contar el terminador nulo
    int len = sizeof(str) - 1;

    printf("Cadena Original: %s\n", str);
    // Almacena los caracteres cifrados como enteros grandes
    long long encrypted[100];
    // Almacena los caracteres descifrados
    char decrypted[100];

    // Cifrado de cada carácter
    for (int i = 0; i < len; i++) {
        encrypted[i] = encryptChar(str[i], e, n);
        // Muestra el mensaje cifrado
        printf("%lld ", encrypted[i]);
    }
    printf("\n");

    // Descifrado de cada carácter
    for (int i = 0; i < len; i++) {
        decrypted[i] = decryptChar(encrypted[i], d, n);
    }
    // Asegura que la cadena descifrada tenga un terminador nulo
    decrypted[len] = '\0';

    // Muestra el mensaje descifrado
    printf("Cadena Descifrada: %s\n", decrypted);
    return 0;
}
