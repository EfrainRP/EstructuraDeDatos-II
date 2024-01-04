def encrypt_cesar(message,key):
    ans=""
    for ch in message.lower():
        if ch.isalpha() :
            asc = ord(ch)
            asc+=key

            while asc > ord('z'):
                asc -=26

            ans+=chr(asc)
        else:
            ans += ch
    print("- Encriptado Cesar hecho")
    return ans

def desencrypt_cesar(message,key):
    ans=""
    for ch in message.lower():       
        if ch.isalpha():
            asc = ord(ch)
            asc-=key
            
            while asc < ord('a'):
                asc += 26

            ans+= chr(asc)
        else:
            ans += ch
    print("- Desencriptado Cesar hecho")
    return ans

def XOR_encrypt_descrypt(message, key, encryp):
    while (key > 255):
        key -= 255

    ans = ""
    for ch in message:
        asc = ord(ch) ^ key

        ans += chr(asc)
    if encryp == True:
        print("- Encriptado XOR hecho")
    else:
        print("- Desencriptado XOR hecho")
    return ans

def read_writeFile(file, mych, myMessage):
    myfile = open(file + '.txt', mych)
    
    if mych == 'r':
        print("\tLeyendo del archivo: " + file + "\n")
        message = ""
        for charFile in myfile:#leer archivo
            message += charFile
        return message
        
    elif mych == 'w':
        myfile.write(myMessage)
        print("\n\tEscribiendo al archivo: " + file + "\n")

print("\t\tENCRIPTACION\n")

mystr=""
menu = 0
while menu!=3:
    print("Seleccione objeto a manejar")
    menu = int(input("[1]Mensaje / [2]Archivo / [3]Salir: "))
    print()

    if menu != 3:
        key = int(input("\tIntroduzca la CLAVE a utilizar: "))
        print()
        if menu==1:
            mystr = str(input("Introduzca el MENSAJE: "))
            print("\nENCRIPTANDO....")

            mystr = XOR_encrypt_descrypt(encrypt_cesar(mystr,key),key,True)
            print("\n\tMENSAJE ENCRIPTADO:",mystr,"\n")

            print("DESENCRIPTANDO....")
            mystr = desencrypt_cesar(XOR_encrypt_descrypt(mystr,key,False),key)
            print("\n\tMENSAJE DESENCRIPTADO:", mystr, "\n")


        elif menu==2:
            file = str(input("Introduzca el ARCHIVO txt: "))
            print()
            mystr = read_writeFile(file, 'r',"")

            print("\nENCRIPTANDO....")
            mystr = XOR_encrypt_descrypt(encrypt_cesar(mystr,key), key, True)
            read_writeFile("encrypt", 'w',mystr)

            mystr = read_writeFile("encrypt", 'r',"")

            print("DESENCRIPTANDO....")
            mystr = desencrypt_cesar(XOR_encrypt_descrypt(mystr,key,False), key)
            read_writeFile("desencrypt", 'w', mystr)

print("\t\tFIN del programa")
