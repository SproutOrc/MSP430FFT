#include "fft.h"

// set up twiddle constants in factor 
Complex const factor[H_NUM] = {
    {1.000000, -0.000000}, {0.998795, -0.0490677}, {0.995185, -0.0980171}, {0.989177, -0.146730},
    {0.980785, -0.195090}, {0.970031, -0.2429800}, {0.956940, -0.2902850}, {0.941544, -0.336890},
    {0.923880, -0.382683}, {0.903989, -0.4275550}, {0.881921, -0.4713970}, {0.857729, -0.514103},
    {0.831470, -0.555570}, {0.803208, -0.5956990}, {0.773010, -0.6343930}, {0.740951, -0.671559},
    {0.707107, -0.707107}, {0.671559, -0.7409510}, {0.634393, -0.7730100}, {0.595699, -0.803208},
    {0.555570, -0.831470}, {0.514103, -0.8577290}, {0.471397, -0.8819210}, {0.427555, -0.903989},
    {0.382683, -0.923880}, {0.336890, -0.9415440}, {0.290285, -0.9569400}, {0.242980, -0.970031},
    {0.195090, -0.980785}, {0.146730, -0.9891770}, {0.0980172, -0.995185}, {0.0490677, -0.998795},
    {0.000000, -1.000000}, {-0.0490676, -0.998795},{-0.0980171, -0.995185},{-0.14673, -0.989177},
    {-0.19509, -0.980785}, {-0.242980, -0.970031}, {-0.290285, -0.956940}, {-0.33689, -0.941544},
    {-0.382683, -0.92388}, {-0.427555, -0.903989}, {-0.471397, -0.881921}, {-0.514103,-0.857729},
    {-0.55557, -0.831470}, {-0.595699, -0.803208}, {-0.634393, -0.773010}, {-0.671559, -0.740951},
    {-0.707107, -0.707107},{-0.740951, -0.671559}, {-0.773010, -0.634393}, {-0.803208,-0.595699},
    {-0.83147, -0.555570}, {-0.857729, -0.514103}, {-0.881921, -0.471397}, {-0.903989, -0.427555},
    {-0.92388, -0.382683}, {-0.941544, -0.336890}, {-0.956940, -0.290285}, {-0.970031, -0.24298},
    {-0.980785, -0.19509}, {-0.989177, -0.146731}, {-0.995185, -0.0980172},{-0.998795, -0.0490677}
};

void imagZero () 
{
    for (int i =  0; i < NUM; i++) {
        data[i].imag = 0.0;
    }
}

void addComplex(Complex *getResult, Complex *A, Complex *withB) {
    getResult->real = A->real + withB->real;
    getResult->imag = A->imag + withB->imag;
}

void subComplex(Complex *getResult, Complex *A, Complex *withB) {
    getResult->real = A->real - withB->real;
    getResult->imag = A->imag - withB->imag;
}

void mulComplex(Complex *getResult, Complex *A, Complex *withB) {
    getResult->real = A->real * withB->real - A->imag * withB->imag;
    getResult->imag = A->real * withB->imag + A->imag * withB->real;
}

//input sample array, # of points
void transform() 
{
    //temporary storage variables 
    Complex topData;
    Complex lowData;
    Complex dataIndex;
    //difference between top/lower leg
    int leg_diff;
    int lower_leg;
    //index/step through twiddle constant 
    int index = 0;
    //step between values
    int step = 1;
    //difference between upper & lower legs
    leg_diff = H_NUM;
    
    //for N-point FFT
    for (int i = 0; i < SERIES; i++)                   
    {
        index = 0;
        for (int j = 0; j < leg_diff; j++) {
            for (int upper_leg = j; upper_leg < NUM; upper_leg += (2 * leg_diff)) {
                lower_leg = upper_leg + leg_diff;

                addComplex(&topData, &data[upper_leg], &data[lower_leg]);
                subComplex(&lowData, &data[upper_leg], &data[lower_leg]);
                dataIndex.real = factor[index].real;
                dataIndex.imag = factor[index].imag;
                mulComplex(&data[lower_leg], &lowData, &dataIndex);
                data[upper_leg].real = topData.real;
                data[upper_leg].imag = topData.imag;
            }
            index += step;
        }

        leg_diff >>= 1;
        step *= 2;
    }
}

//bit reversal for resequencing data
//Rader algorithm
//Input reverse
void inReverse () { 
    Complex Temp;   
    int j = 0;
    int k = 0;
    
    for (int i = 1; i < (NUM - 1); i++) {
        k = H_NUM;

        while (k <= j) {
            j = j - k;
            k = k / 2;
        }
        j = j + k;
        if (i < j) {
            Temp.real = data[j].real;
            Temp.imag = data[j].imag;

            data[j].real = data[i].real;
            data[j].imag = data[i].imag;

            data[i].real = Temp.real;
            data[i].imag = Temp.imag;
        }
    }
}

void FFT() {
    imagZero();
    transform();
    inReverse();
}