#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
    int numVectorsToCreate, numVectorsToResize;
    int vectorIndex, vectorSize;
    int dataType;
    string dataTypeStr;
    string fileName;

    /** 
     * Main loop to take user input and generate vectors.
     * The loop continues until the user inputs "#".
     */
    cout << "Input # for quit." << endl;
    while (true)
    {
        cout << "Input the filename: ";
        cin >> fileName;

        // Exit condition
        if (fileName == "#") break;

        cout << "Input the number of vectors to be created: ";
        cin >> numVectorsToCreate;
        cout << "Input the number of vectors to be resized: ";
        cin >> numVectorsToResize;

        ofstream fout(fileName.c_str(), ios::out);

        // Test if the file is opened successfully
        if (!fout)
        {
            cout << "Error opening file." << endl;
            return 0;
        }

        // Write the number of vectors to the file
        fout << numVectorsToCreate << endl;

        /** 
         * Generate numVectorsToCreate number of vectors with random sizes and types
         * and write them to the file.
         */
        for (int i = 0; i < numVectorsToCreate; i++)
        {
            vectorSize = rand() % 10000; // Generate a random size between 0 and 9999
            dataType = rand() % 4 + 1;   // Generate a random type between 1 and 4

            switch (dataType)
            {
                case 1: dataTypeStr = "int"; break;
                case 2: dataTypeStr = "float"; break;
                case 3: dataTypeStr = "double"; break;
                case 4: dataTypeStr = "class"; break;
                default: break;
            }
            fout << vectorSize << " " << dataTypeStr << endl;
        }

        /** 
         * Generate numVectorsToResize number of resize operations with random indices and sizes
         * and write them to the file.
         */
        for (int i = 0; i < numVectorsToResize; i++)
        {
            vectorIndex = rand() % numVectorsToCreate; // Generate a random index within the created vector range
            vectorSize = rand() % 10000;  // Generate a random size between 0 and 9999
            if (i == numVectorsToResize - 1) 
                fout << vectorIndex << " " << vectorSize;
            else 
                fout << vectorIndex << " " << vectorSize << endl;
        }

        fout.close();
        cout << "Finish successfully!" << endl;
    }
    return 0;
}
