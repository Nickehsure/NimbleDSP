/*
Copyright (c) 2014, James Clay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "RealVector.h"
#include "gtest/gtest.h"


extern bool FloatsEqual(double float1, double float2);


TEST(RealVectorInit, Size) {
	NimbleDSP::RealVector<double> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
}

TEST(RealVectorInit, Array) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

TEST(RealVectorInit, Vector) {
    double array[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    std::vector<double> inputData (array, array + sizeof(array) / sizeof(array[0]) );
	NimbleDSP::RealVector<double> buf(inputData);
    
    EXPECT_EQ(inputData.size(), buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf.vec[i]);
    }
}

// Operator tests
TEST(RealVectorOperators, PlusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 += buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf1.vec[i]);
        EXPECT_EQ(inputData[i], buf2.vec[i]);
    }
}

TEST(RealVectorOperators, PlusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf += 5;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]+5, buf.vec[i]);
    }
}

TEST(RealVectorOperators, PlusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData, numElements);
    NimbleDSP::RealVector<double> buf3(0);
    
    buf3 = buf1 + buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(2*inputData[i], buf3.vec[i]);
    }
}

TEST(RealVectorOperators, PlusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(0);
    
    buf2 = buf1 + 32.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] + 32.0, buf2.vec[i]);
    }
}

TEST(RealVectorOperators, MinusEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 -= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealVectorOperators, MinusEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf -= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]-11, buf.vec[i]);
    }
}

TEST(RealVectorOperators, MinusBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    NimbleDSP::RealVector<double> buf3(0);
    
    buf3 = buf1 - buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - inputData2[i], buf3.vec[i]);
    }
}

TEST(RealVectorOperators, MinusScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(0);
    
    buf2 = buf1 - 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] - 15, buf2.vec[i]);
    }
}

TEST(RealVectorOperators, MultiplyEqualsBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 *= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealVectorOperators, MultiplyEqualsScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf *= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*11, buf.vec[i]);
    }
}

TEST(RealVectorOperators, MultiplyBuf) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    NimbleDSP::RealVector<double> buf3(0);
    
    buf3 = buf1 * buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]*inputData2[i], buf3.vec[i]);
    }
}

TEST(RealVectorOperators, MultiplyScalar) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(0);
    
    buf2 = buf1 * 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] * 15, buf2.vec[i]);
    }
}

TEST(RealVectorOperators, DivideEqualsBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    
    EXPECT_EQ(numElements, buf1.vec.size());
    
    buf1 /= buf2;
    for (unsigned i=0; i<buf1.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf1.vec[i]);
        EXPECT_EQ(inputData2[i], buf2.vec[i]);
    }
}

TEST(RealVectorOperators, DivideEqualsScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf /= 11;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/11, buf.vec[i]);
    }
}

TEST(RealVectorOperators, DivideBuf) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    double inputData2[] = {-1, 2, 4, 6, 1, 3, 5, 7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
    NimbleDSP::RealVector<double> buf3(0);
    
    buf3 = buf1 / buf2;
    EXPECT_EQ(numElements, buf3.vec.size());
    for (unsigned i=0; i<buf3.vec.size(); i++) {
        EXPECT_EQ(inputData[i]/inputData2[i], buf3.vec[i]);
    }
}

TEST(RealVectorOperators, DivideScalar) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(0);
    
    buf2 = buf1 / 15.0;
    EXPECT_EQ(numElements, buf2.vec.size());
    for (unsigned i=0; i<buf2.vec.size(); i++) {
        EXPECT_EQ(inputData[i] / 15.0, buf2.vec[i]);
    }
}

TEST(RealVectorOperators, UnaryMinus) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(numElements, buf.vec.size());
    
    buf = -buf;
    EXPECT_EQ(numElements, buf.vec.size());
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(-inputData[i], buf.vec[i]);
    }
}

TEST(RealVectorOperators, Indexing) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(numElements);
    
    for (unsigned i=0; i<numElements; i++) {
        buf[i] = inputData[i];
    }
    
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealVectorOperators, Equality) {
    double inputData[] = {1, 3, 5, 7.12, 2, 4, 6, 8};
    double inputData2[] = {0, 2, 4, 6, 1, 3, 5, 7};
    double inputData3[] = {0, 2, 4, 6, 1, 3, 5, 7, 8};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    unsigned numElements3 = sizeof(inputData3)/sizeof(inputData3[0]);
	NimbleDSP::RealVector<double> buf1(inputData, numElements);
	NimbleDSP::RealVector<double> buf2(inputData2, numElements);
	NimbleDSP::RealVector<double> buf3(inputData3, numElements3);
    
    EXPECT_FALSE(buf1 == buf2);
    EXPECT_TRUE(buf1 != buf2);
    EXPECT_FALSE(buf3 == buf2);
    EXPECT_TRUE(buf3 != buf2);
    EXPECT_TRUE(buf1 == buf1);
    EXPECT_FALSE(buf1 != buf1);
}

TEST(RealVectorStatistics, Mean) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(450.015, mean(buf)));
}

TEST(RealVectorStatistics, Var) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(60008.57322857144, var(buf)));
}

TEST(RealVectorStatistics, StdDev) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_TRUE(FloatsEqual(244.9664736827704, stdDev(buf)));
}

TEST(RealVectorStatistics, Median) {
    double inputData[] = {100, 300, 500, 700.12, 200, 400, 600, 800};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(450, median(buf));
    buf.vec.push_back(-10000);
    EXPECT_EQ(400, median(buf));
}

TEST(RealVectorMethods, Rotate) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    rotate(buf, numElements);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    
    rotate(buf, 3);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[(3 + i) % numElements], buf[i]);
    }
    
    rotate(buf, -1);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[(2 + i) % numElements], buf[i]);
    }
}

TEST(RealVectorMethods, Reverse) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 9};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[numElements-i-1], buf[i]);
    }
    reverse(buf);
    for (unsigned i=0; i<buf.vec.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Max) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(8.37, max(buf));
    unsigned maxLoc;
    EXPECT_EQ(8.37, max(buf, &maxLoc));
    EXPECT_EQ(3, maxLoc);
}

TEST(RealVectorMethods, Min) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(2, min(buf));
    unsigned minLoc;
    EXPECT_EQ(2, min(buf, &minLoc));
    EXPECT_EQ(0, minLoc);
    
    reverse(buf);
    EXPECT_EQ(2, min(buf));
    EXPECT_EQ(2, min(buf, &minLoc));
    EXPECT_EQ(7, minLoc);
}

TEST(RealVectorMethods, Find) {
    double inputData[] = {2, 4, 6, 8.37, 3, 5, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(-1, find(buf, 9.0));
    EXPECT_EQ(4, find(buf, 3.0));
}

TEST(RealVectorMethods, Pow) {
    double inputData[] = {2, 0, 6, 8.37, 3, 1, 7, 3};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    pow(buf, 3.0);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i]*inputData[i]*inputData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Saturate) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    double expectedData[] = {1, -5, 5, 3, 5, -2, -5, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    saturate(buf, 5.0);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Abs) {
    double inputData[] = {1, -10, 8, 0, 6.92, -2, -9, 1};
    double expectedData[] = {1, 10, 8, 0, 6.92, 2, 9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    abs(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Resize) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    buf.resize(11);
    EXPECT_EQ(11, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
    
    resize(buf, 4);
    EXPECT_EQ(4, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Pad) {
    double inputData[] = {1, -10, 8, 3, 6.92, -2, -9, 1};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    pad(buf, 5);
    EXPECT_EQ(13, buf.size());
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(inputData[i], buf[i]);
    }
    for (unsigned i=numElements; i<buf.size(); i++) {
        EXPECT_EQ(0, buf[i]);
    }
}

TEST(RealVectorMethods, Exp) {
    double inputData[] = {1, -10, 8, 0, 6.92, -2, -9, 1};
    double expectedData[] = {2.71828183, 0.00004540, 2980.95798704, 1.00000000, 1012.31999453, 0.13533528, 0.00012341, 2.71828183};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    exp(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealVectorMethods, Log) {
    double inputData[] = {1, 10001.3, 8, .0001, 6.92, 2, 9, 1};
    double expectedData[] = {0, 9.21047036, 2.07944154, -9.21034037, 1.93441577, 0.69314718, 2.19722458, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    log(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealVectorMethods, Log10) {
    double inputData[] = {1, 10001.3, 8, .0001, 6.92, 2, 9, 1};
    double expectedData[] = {0, 4.00005645, 0.90308999, -4.00000000, 0.84010609, 0.30103000, 0.95424251, 0};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    log10(buf);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealVectorMethods, Upsample) {
	double inputData[] = { 1, 10001, 8, -5, 6, 2, 9, 1 };
	double expectedData[] = { 1, 0, 0, 10001, 0, 0, 8, 0, 0, -5, 0, 0, 6, 0, 0, 2, 0, 0, 9, 0, 0, 1, 0, 0 };
	double expectedData2[] = { 0, 1, 0, 0, 10001, 0, 0, 8, 0, 0, -5, 0, 0, 6, 0, 0, 2, 0, 0, 9, 0, 0, 1, 0 };
	double expectedData3[] = { 0, 0, 0, 1, 0, 0, 0, 10001, 0, 0, 0, 8, 0, 0, 0, -5, 0, 0, 0, 6, 0, 0, 0, 2, 0, 0, 0, 9, 0, 0, 0, 1 };
	unsigned numElements = sizeof(inputData) / sizeof(inputData[0]);
	NimbleDSP::RealVector<double> bufSave(inputData, numElements);
	NimbleDSP::RealVector<double> buf(0);

	buf = bufSave;
	upsample(buf, 3);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData[i], buf[i]);
	}

	buf = bufSave;
	upsample(buf, 3, 1);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData2[i], buf[i]);
	}

	buf = bufSave;
	upsample(buf, 4, 3);
	for (unsigned i = 0; i<numElements; i++) {
		EXPECT_EQ(expectedData3[i], buf[i]);
	}
}

TEST(RealVectorMethods, FilterOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 2, 0, -5, -20, -35, -50, -65, -72, -70, -58, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, FilterEven) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {1, 2, 2, 0, -5, -14, -35, -56, -77, -90, -94, -88, -71, -42};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, FilterOddTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {2, 0, -5, -20, -35, -50, -65, -72, -70};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, FilterEvenTrim) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5, 6};
    double expectedData[] = {2, 0, -5, -14, -35, -56, -77, -90, -94};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, Sum) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    EXPECT_EQ(-27, sum(buf));
}

TEST(RealVectorMethods, Diff) {
    double inputData[] = {1, 1, 2, 4, 7, 11, 16, 22};
    double expectedData[] = {0, 1, 2, 3, 4, 5, 6};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    diff(buf);
    EXPECT_EQ(numElements-1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, RunningDiff) {
    double inputData[] = {1, 1, 2, 4, 7, 11, 16, 22};
    double expectedData[] = {-1, 0, 1, 2, 3, 4, 5, 6};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    double previousVal = 2;
    diff(buf, previousVal);
    EXPECT_EQ(numElements, buf.size());
    EXPECT_EQ(22, previousVal);
    for (unsigned i=0; i<numElements; i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorFilter, DecimateEvenOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 0, -35, -72, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorFilter, InterpEvenOdd) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 2, 3, 4, 5, 0, -1, -2, -3, -6, -9, -6, -11, -16, -9, -16, -23, -12, -21, -30, -15, -26, -37, -18, -31, -44, -21, -28, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorFilter, Resample1) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    int filterTaps[] = {1, 2, 3, 4, 5};
    double expectedData[] = {1, 3, 5, -1, -3, -9, -11, -9, -23, -21, -15, -37, -31, -21, -35};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::RealVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexFilterOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106), std::complex<double>(-58, 85), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexFilterEven) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5, 6};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 7), std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-14, 77), std::complex<double>(-35, 98), std::complex<double>(-56, 119), std::complex<double>(-77, 140), std::complex<double>(-90, 150), std::complex<double>(-94, 148), std::complex<double>(-88, 133), std::complex<double>(-71, 104), std::complex<double>(-42, 60)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter);
    EXPECT_EQ(input.size() + filter.size() - 1, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexFilterOddTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-20, 65), std::complex<double>(-35, 80), std::complex<double>(-50, 95), std::complex<double>(-65, 110), std::complex<double>(-72, 114), std::complex<double>(-70, 106)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexFilterEvenTrim) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5, 6};
    std::complex<double> expectedData[] = {std::complex<double>(2, 16), std::complex<double>(0, 30), std::complex<double>(-5, 50), std::complex<double>(-14, 77), std::complex<double>(-35, 98), std::complex<double>(-56, 119), std::complex<double>(-77, 140), std::complex<double>(-90, 150), std::complex<double>(-94, 148)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
    std::vector< std::complex<double> > scratchBuf;
	NimbleDSP::ComplexVector<double> buf(inputData, numElements, NimbleDSP::TIME_DOMAIN, &scratchBuf);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    
    conv(buf, filter, true);
    EXPECT_EQ(input.size(), buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}
TEST(RealVectorMethods, ComplexDecimateEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(0, 30), std::complex<double>(-35, 80), std::complex<double>(-72, 114), std::complex<double>(-35, 50)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    
    decimate(buf, rate, filter);
    EXPECT_EQ((input.size() + filter.size() - 1 + (rate - 1))/rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexInterpEvenOdd) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(2, 4), std::complex<double>(3, 6), std::complex<double>(4, 11), std::complex<double>(5, 16), std::complex<double>(0, 9), std::complex<double>(-1, 16), std::complex<double>(-2, 23), std::complex<double>(-3, 12), std::complex<double>(-6, 21), std::complex<double>(-9, 30), std::complex<double>(-6, 15), std::complex<double>(-11, 26), std::complex<double>(-16, 37), std::complex<double>(-9, 18), std::complex<double>(-16, 31), std::complex<double>(-23, 44), std::complex<double>(-12, 21), std::complex<double>(-21, 36), std::complex<double>(-30, 51), std::complex<double>(-15, 24), std::complex<double>(-26, 41), std::complex<double>(-37, 58), std::complex<double>(-18, 27), std::complex<double>(-31, 46), std::complex<double>(-44, 65), std::complex<double>(-21, 30), std::complex<double>(-28, 40), std::complex<double>(-35, 50), std::complex<double>(0, 0), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int rate = 3;
    
    interp(buf, rate, filter);
    EXPECT_EQ(input.size()*rate + filter.size() - rate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorMethods, ComplexResample1) {
    std::complex<double> inputData[] = {std::complex<double>(1, 2), std::complex<double>(0, 3), std::complex<double>(-1, 4), std::complex<double>(-2, 5), std::complex<double>(-3, 6), std::complex<double>(-4, 7), std::complex<double>(-5, 8), std::complex<double>(-6, 9), std::complex<double>(-7, 10)};
    double filterTaps[] = {1, 2, 3, 4, 5};
    std::complex<double> expectedData[] = {std::complex<double>(1, 2), std::complex<double>(3, 6), std::complex<double>(5, 16), std::complex<double>(-1, 16), std::complex<double>(-3, 12), std::complex<double>(-9, 30), std::complex<double>(-11, 26), std::complex<double>(-9, 18), std::complex<double>(-23, 44), std::complex<double>(-21, 36), std::complex<double>(-15, 24), std::complex<double>(-37, 58), std::complex<double>(-31, 46), std::complex<double>(-21, 30), std::complex<double>(-35, 50), std::complex<double>(0, 0)};
    unsigned numElements = sizeof(inputData)/sizeof(inputData[0]);
	NimbleDSP::ComplexVector<double> buf(inputData, numElements);
    numElements = sizeof(filterTaps)/sizeof(filterTaps[0]);
    NimbleDSP::RealVector<double> filter(filterTaps, numElements);
    NimbleDSP::ComplexVector<double> input = buf;
    int interpRate = 3;
    int decimateRate = 2;
    
    resample(buf, interpRate, decimateRate, filter);
    EXPECT_EQ((input.size()*interpRate + filter.size()-1 - (interpRate-1) + decimateRate-1)/decimateRate, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_EQ(expectedData[i], buf[i]);
    }
}

TEST(RealVectorDataGen, Tone0) {
    double expectedData[] = {0.84147098, -0.41304825, -0.96083378, 0.13538625, 0.99995773, 0.15358181, -0.95557562, -0.42972431, 0.83139377, 0.66998070, -0.63778257, -0.85428728, 0.39091040, 0.96725267, -0.11139347, -0.99944319, -0.17742589, 0.94817061, 0.45142849, -0.81771668, -0.68773247, 0.61897557, 0.86660420};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	NimbleDSP::RealVector<double> buf(numElements);
    
    tone(buf, -10007.3, 44100.0, 1.0);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealVectorDataGen, Tone) {
    double expectedData[] = {0.47942554, 0.54298501, 0.60357344, 0.66085930, 0.71452915, 0.76428932, 0.80986754, 0.85101442, 0.88750482, 0.91913907, 0.94574408, 0.96717428, 0.98331241, 0.99407016, 0.99938867, 0.99923884, 0.99362149, 0.98256736, 0.96613693, 0.94442010, 0.91753570, 0.88563084, 0.84888009, 0.80748452, 0.76167066, 0.71168918};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	NimbleDSP::RealVector<double> buf;
    
    tone(buf, 519.3, 44100.0, 0.5, 26);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

TEST(RealVectorMethods, Modulate) {
    double inputData[] = {1, 0, -1, -2, -3, -4, -5, -6, -7};
    double expectedData[] = {0.86602540,0.00000000,0.95931397,-1.27484798,-1.37129378,3.99025620,-1.64433323,-4.43073204,6.37478563};
    unsigned numElements = sizeof(expectedData)/sizeof(expectedData[0]);
	NimbleDSP::RealVector<double> buf(inputData, numElements);
    
    modulate(buf, 283.0, 900.0, M_PI/3);
    EXPECT_EQ(numElements, buf.size());
    for (unsigned i=0; i<buf.size(); i++) {
        EXPECT_TRUE(FloatsEqual(expectedData[i], buf[i]));
    }
}

