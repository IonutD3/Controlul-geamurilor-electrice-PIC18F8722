
#include <xc.h>
#include <string.h>

// Variabila in care este stocat caracterul primit prin UART
unsigned char c;

// Functie pentru initializarea modulului USART
void init_USART()
{
    // Selectarea modului asincron al USART
    CSRC = 1;
    SYNC = 0;

    // Activarea modului de baud rate high speed
    BRGH = 1;

    // Utilizarea registrului SPBRG pe 8 biti
    BAUDCONbits.BRG16 = 0;

    // Configurarea vitezei de comunicatie la 19200 bps
    SPBRG1 = 12;

    // Activarea transmisiei UART
    TXEN = 1;

    // Activarea receptiei continue UART
    CREN = 1;

    // RC6 - pin pentru transmisia UART
    TRISCbits.RC6 = 0;

    // RC7 - pin pentru receptia UART
    TRISCbits.RC7 = 1;

    // Activarea modulului serial
    SPEN = 1;

    // Activarea intreruperilor globale
    GIE = 1;

    // Activarea intreruperilor periferice
    PEIE = 1;

    // Activarea intreruperii de transmisie
    TX1IE = 1;

    // Activarea intreruperii de receptie
    RC1IE = 1;
}

// Functie pentru transmiterea unui caracter prin UART
void write_serial(char c)
{
    // Asteapta pana cand registrul de transmisie este disponibil
    while(!TX1IF);

    // Transmite caracterul
    TXREG = c;
}

// Functie pentru citirea unui caracter primit prin UART
void read_serial()
{
    // Asteapta pana cand exista un caracter receptionat
    while(!RC1IF);

    // Salveaza caracterul primit
    c = RCREG1;
}

// Functie pentru transmiterea unui sir de caractere
void write_ms(char ch[])
{
    // Transmite caracterele din sir unul cate unul
    for(int i = 0; i <= strlen(ch); i++)
    {
        write_serial(ch[i]);
    }
}

// Rutina de tratare a intreruperilor
void interrupt ISR()
{
    // Verifica intreruperea de transmisie
    if(TX1IF)
    {
        // Dezactiveaza intreruperea de transmisie
        TX1IE = 0;
    }

    // Verifica daca a fost primit un caracter prin UART
    if(RC1IF)
    {
        // Citeste caracterul primit
        read_serial();

        // Interpreteaza comanda primita
        switch(c)
        {
            // 0 - coborare geam sofer
            case '0':
                RD0 = 1;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geam sofer");
                write_serial(0x0d);
                break;

            // 1 - ridicare geam sofer
            case '1':
                RD0 = 0;
                RD1 = 1;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Ridicare geam sofer");
                write_serial(0x0d);
                break;

            // 2 - coborare geam pasager
            case '2':
                RD0 = 0;
                RD1 = 0;
                RD2 = 1;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geam pasager");
                write_serial(0x0d);
                break;

            // 3 - ridicare geam pasager
            case '3':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 1;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Ridicare geam pasager");
                write_serial(0x0d);
                break;

            // 4 - coborare geam stanga spate
            case '4':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 1;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geam stanga spate");
                write_serial(0x0d);
                break;

            // 5 - ridicare geam stanga spate
            case '5':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 1;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Ridicare geam stanga spate");
                write_serial(0x0d);
                break;

            // 6 - coborare geam dreapta spate
            case '6':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 1;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geam dreapta spate");
                write_serial(0x0d);
                break;

            // 7 - ridicare geam dreapta spate
            case '7':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 1;

                write_serial(0x0d);
                write_ms("Ridicare geam dreapta spate");
                write_serial(0x0d);
                break;

            // 8 - coborare toate geamurile
            case '8':
                RD0 = 1;
                RD1 = 0;
                RD2 = 1;
                RD3 = 0;
                RD4 = 1;
                RD5 = 0;
                RD6 = 1;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare toate geamurile");
                write_serial(0x0d);
                break;

            // 9 - ridicare toate geamurile
            case '9':
                RD0 = 0;
                RD1 = 1;
                RD2 = 0;
                RD3 = 1;
                RD4 = 0;
                RD5 = 1;
                RD6 = 0;
                RD7 = 1;

                write_serial(0x0d);
                write_ms("Ridicare toate geamurile");
                write_serial(0x0d);
                break;

            // q - coborare geamuri fata
            case 'q':
                RD0 = 1;
                RD1 = 0;
                RD2 = 1;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geamuri fata");
                write_serial(0x0d);
                break;

            // w - ridicare geamuri fata
            case 'w':
                RD0 = 0;
                RD1 = 1;
                RD2 = 0;
                RD3 = 1;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Ridicare geamuri fata");
                write_serial(0x0d);
                break;

            // a - coborare geamuri spate
            case 'a':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 1;
                RD5 = 0;
                RD6 = 1;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geamuri spate");
                write_serial(0x0d);
                break;

            // s - ridicare geamuri spate
            case 's':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 1;
                RD6 = 0;
                RD7 = 1;

                write_serial(0x0d);
                write_ms("Ridicare geamuri spate");
                write_serial(0x0d);
                break;

            // e - coborare geamuri din partea stanga
            case 'e':
                RD0 = 1;
                RD1 = 0;
                RD2 = 0;
                RD3 = 0;
                RD4 = 1;
                RD5 = 0;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geamuri stanga");
                write_serial(0x0d);
                break;

            // r - ridicare geamuri din partea stanga
            case 'r':
                RD0 = 0;
                RD1 = 1;
                RD2 = 0;
                RD3 = 0;
                RD4 = 0;
                RD5 = 1;
                RD6 = 0;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Ridicare geamuri stanga");
                write_serial(0x0d);
                break;

            // d - coborare geamuri din partea dreapta
            case 'd':
                RD0 = 0;
                RD1 = 0;
                RD2 = 1;
                RD3 = 0;
                RD4 = 0;
                RD5 = 0;
                RD6 = 1;
                RD7 = 0;

                write_serial(0x0d);
                write_ms("Coborare geamuri dreapta");
                write_serial(0x0d);
                break;

            // f - ridicare geamuri din partea dreapta
            case 'f':
                RD0 = 0;
                RD1 = 0;
                RD2 = 0;
                RD3 = 1;
                RD4 = 0;
                RD5 = 0;
                RD6 = 0;
                RD7 = 1;

                write_serial(0x0d);
                write_ms("Ridicare geamuri dreapta");
                write_serial(0x0d);
                break;
        }

        // Reseteaza flag-ul de receptie UART
        RC1IF = 0;
    }
}

// Functia principala
void main(void)
{
    // Configureaza PORTD ca iesire
    TRISD = 0x0;

    // Initializeaza iesirile PORTD cu valoarea 0
    LATD = 0x0;

    // Initializeaza modulul UART
    init_USART();

    // Afiseaza comenzile disponibile prin interfata seriala
    write_ms("Apasati 0 Coborare geam sofer;1 Ridicare geam sofer;2 Coborare geam pasager;3 Ridicare geam pasager;4 Coborare geam stanga spate;5 Ridicare geam stanga spate;");
    write_serial(0x0d);

    write_ms("Apasati 6 Coborare geam dreapta spate;7 Ridicare geam dreapta spate;8 Coborare toate geamurile;9 Ridicare toate geamurile");
    write_serial(1x0d);

    write_ms("Apasati q Coborare geamuri fata;w Ridicare geamuri fata;a Coborare geamuri spate;s Ridicare geamuri spate;");
    write_serial(2x0d);

    write_ms("Apasati e Coborare geamuri stanga;r Ridicare geamuri stanga;d Coborare geamuri dreapta;f Ridicare geamuri dreapta;");
    write_serial(3x0d);

    // Bucla principala ramane activa.
    // Procesarea comenzilor se realizeaza prin intreruperi.
    while (1)
    {
    }
}
