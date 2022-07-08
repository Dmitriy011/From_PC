#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

typedef double arr[20];

int main()
{
    bool f;
    int n, i, j, k;
    double a[20][20];
    arr b, xk, xkk, gk, gkk, dk, dkk, c;
    ifstream inp("input.txt"); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    inp >> n;
    double t, e, p1, p2, p, sk, xkp, xkkp, z;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            inp >> t;
            a[i][j] = t;
            //cout << t << " ";
        }
    //cout << endl;
    for (i = 0; i < n; i++)
    {
        inp >> t;
        //cout << t << " ";
        b[i] = t;
        gk[i] = 0;
        gkk[i] = 0;
        dk[i] = 0;
        dkk[i] = 0;
        xk[i] = 0;
    }
    cout << endl;
    inp.close();
    cout << "������� ��������: ";
    cin >> e;
    k = 0;
    f = false;
    do
    {
        //-------------------��� 1 gk= A*xkk - b, k - ������� ��������, kk - ����������
        if (k == 1) f = true;
        //cout << "��� 1 " << k;
        for (i = 0; i < n; i++)
        {
            c[i] = 0;
            for (j = 0; j < n; j++)
                c[i] = c[i] + a[i][j] * xk[i];
        }
        for (i = 0; i < n; i++)
            gk[i] = c[i] - b[i];
        //cout << "������ gk ";
        //for(i=0;i<n;i++)
        //  cout << gk[i] << " ";
        //cout << endl;

        //------------------��� 2 dk=...
        //cout << "��� 2 ";
        p1 = 0; p2 = 0; p = 0;
        for (i = 0; i < n; i++)
        {
            p1 = p1 + gk[i] * gk[i];
            p2 = p2 + gkk[i] * gkk[i];
            //  cout << "p1 " << p1 << " p2 " << p2 << endl;
        }
        if (p2 != 0)
            p = p1 / p2;
        for (i = 0; i < n; i++)
            dk[i] = -gk[i] + p * dkk[i];

        //cout << "������ dk ";
        //for(i=0;i<n;i++)
         //cout << dk[i] << " ";
        //cout << endl;

        //-----------------��� 3 sk=...
        //cout << "��� 3 ";
        p1 = 0; p2 = 0;
        for (i = 0; i < n; i++)
            p1 = p1 + dk[i] * gk[i];

        for (i = 0; i < n; i++)
        {
            c[i] = 0;
            for (j = 0; j < n; j++)
            {
                //cout << endl;
                //cout << " ������� � � SK ";
                c[i] = c[i] + dk[j] * a[i][j];
                //cout << " i,j " << i << "," << j << " dkj " << dk[j] << " aij " << a[i][j] << " ci " << c[i] << endl;
            }
        }

        for (i = 0; i < n; i++)
            p2 = p2 + c[i] * dk[i];

        //cout << "�1 � �2" << p1 << " " << p2;
        sk = p1 / p2;

        //cout << "sk " << sk << endl;
        //------------------��� 4 xk=
        //cout << "��� 4 ";
        for (i = 0; i < n; i++)
            xk[i] = xkk[i] + sk * dk[i];

        //cout << "������ xk ";
            //for(i=0;i<n;i++)
            //  cout << xk[i] << " ";
        //cout << endl;

        //-----------------�������
        for (i = 0; i < n; i++)
        {
            dkk[i] = dk[i];
            gkk[i] = gk[i];
            xkk[i] = xk[i];
        }

        // --------------���� ��� ��������
        p1 = 0; p2 = 0;
        for (i = 0; i < n; i++)
        {
            p1 = p1 + xk[i] * xk[i];
            p2 = p2 + xkk[i] * xkk[i];
        }
        xkp = sqrt(p1);
        xkkp = sqrt(p2);
        if (xkp > xkkp)
            z = xkp - xkkp;
        else
            z = xkkp - xkp;
        cout << z << " ";
        k = k + 1;
        if (k < 2) z = e * 2;
    } while (z >= e);

    for (i = 0; i < n; i++)
        cout << xk[i] << " ";
    return 0;
}