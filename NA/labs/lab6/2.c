void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[])
{
    double h[MAX_N];
    double al[MAX_N];
    double l[MAX_N];
    double z[MAX_N];
    double u[MAX_N];

    if (Type == 1)
    { 
        for (int i = 0; i < n; i++)
            h[i] = x[i + 1] - x[i];

        for (int i = 0; i <= n; i++)
            a[i+1] = f[i];
        
        al[0] = 3 * (f[1] - f[0]) / h[0] - 3 * s0;
        al[n] = 3 * sn - 3 * (f[n] - f[n - 1]) / h[n - 1];
        
        for (int i = 1; i < n; i++)
            al[i] = 3 / h[i] * (f[i + 1] - f[i]) - 3 / h[i - 1] * (f[i] - f[i - 1]);

            l[0] = 2 * h[0];
            u[0] = 0.5;
            z[0] = al[0] / l[0];

        for (int i = 1; i < n; i++)
        {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
            u[i] = h[i] / l[i];
            z[i] = (al[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[n] = h[n - 1] * (2 - u[n - 1]);
        z[n] = (al[n] - h[n - 1] * z[n - 1]) / l[n];
        c[n+1] = z[n];

        for (int j = n - 1; j >= 0; j--)
        {
            c[j+1] = z[j] - u[j] * c[j + 2];
            b[j+1] = (a[j + 2] - a[j+1]) / h[j] - h[j] * (c[j + 2] + 2 * c[j+1]) / 3;
            d[j+1] = (c[j + 2] - c[j+1]) / (3 * h[j]);
        }
    }
    else 
    {   
        for (int i = 0; i < n; i++)
            h[i] = x[i + 1] - x[i];

        for (int i = 0; i <= n; i++)
            a[i+1] = f[i];

        for (int i = 1; i < n; i++)
            al[i] = 3 / h[i] * (f[i + 1] - f[i]) - 3 / h[i - 1] * (f[i] - f[i - 1]);

        l[0] = 1;
        u[0] = 0;
        z[0] = s0/2;
        
        for (int i = 1; i < n; i++)
        {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (al[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[n] = 1;
        z[n] = sn/2;
        c[n+1] = sn/2;

        for (int j = n - 1; j >= 0; j--)
        {
            c[j+1] = z[j] - u[j] * c[j + 2];
            b[j+1] = (a[j + 2] - a[j+1]) / h[j] - h[j]*(c[j + 2] + 2 * c[j+1]) / 3;
            d[j+1] = (c[j + 2] - c[j+1]) / (3 * h[j]);
        }
    }   
}

double S(double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[])
{
    int i = 0;
    if (x[0]>t||x[n]<t) return Fmax;
    while (t > x[i]) i++;
    if (t == x[0]) i++;
    return a[i] + b[i] * (t - x[i - 1]) + c[i] * (t - x[i - 1]) * (t - x[i - 1]) + d[i] * (t - x[i - 1]) * (t - x[i - 1]) * (t - x[i - 1]);
}
