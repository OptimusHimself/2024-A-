#include <stdio.h>
#include "math.h"

#define pi 3.1415926

#define LongBar 2.86
#define shortBar 1.65
#define totalLengthOfTheDragon 369.16
#define time 300
#define personNumber 223

#define segmentNumber_spire 54900
#define segmentNumber_troop 36916

void printArr_double(double arr[])
{
    int size = 54900; // 计算数组中元素的数量
    printf("The elements in the array are:\n");
    for (int i = 0; i < size; i++)
    {
        printf("line%d:  %lf \n", i, arr[i]); // 打印当前元素
    }
    printf("\n"); // 打印换行符
}

void DotPrinter(double arr_x[], double arr_y[], int count)
{
    // int count = 54901;
    for (int i = 0; i < count; i++)
    {
        printf("\nLine%d: x=%lf      y=%lf", i + 1, arr_x[i], arr_y[i]);
    }
}

void findTranscend(int IndexOfHead[], double DotDistance[], double dotArr_x[], double dotArr_y[], double HeadLoca_x[], double HeadLoca_y[])
{
    // Dotdistance for相加求和多个if条件为dotarr_y/x找位置if里面套if
    double sum = 0; // 每一小段的和
    int i = 0;

    // t 命名取自time,从0(秒)开始,便于后续对HeadLocation数组赋值. 利用t,不断更新步长总和
    for (int t = 0; t < 300; t++)
    {
        while (sum < t + 2)
        {
            if (sum >= 1 + t)
            {
                // 判断两头到1m之间的距离,从而找到龙头哥一米处的近似点.并将近似点的坐标赋给HeadLocation的相应index
                if (sum - 1 - t >= t + 1 + DotDistance[i] - sum) // 超出的那一段：DotDistance[i],由DotDistance index 和 DotArr index的对应关系，选后面那一个点DotArr[i]
                {
                    // printf("\nWE ARe In the assignemtn state");
                    HeadLoca_x[t] = dotArr_x[i];
                    HeadLoca_y[t] = dotArr_y[i];
                    IndexOfHead[t] = i;
                    break;
                }

                //  sum已经超出龙头哥的位置了，且transcent段（DotDistance[i]），前part(dotArr[i+1]__A) 比 后part（A__dotArr[i])短。
                // 选dotArr[i+1]以近似龙头哥此时的位置
                else
                {
                    HeadLoca_x[t] = dotArr_x[i + 1];
                    HeadLoca_y[t] = dotArr_y[i + 1];
                    IndexOfHead[t] = i;

                    break;
                }
            }
            sum = sum + DotDistance[i];
            i++;
        }
    }
}

// 取点函数
void fillDotArr(double x[], double y[])
{
    // theta 等价于theta_Final/10 ,from 5490 to 0 （故后面除1800和3600）
    int theta_Final = 54900;
    double radius_;
    double radius = 8.8;
    for (; theta_Final > 0; theta_Final--)
    {
        // to represent the continuous decreasing of radius_ while the dot moving
        radius_ = radius - (54900 - theta_Final) * 0.55 / 3600;

        x[54900 - theta_Final] = radius_ * sin(theta_Final * pi / 1800);
        y[54900 - theta_Final] = radius_ * -cos(theta_Final * pi / 1800);
    }
}

// 利用两点之间距离公式计算相邻两点的距离.并存入DotDistance数组中
double fillArrDistance(double dotArr_x[], double dotArr_y[], double DotDistance[])
{
    double sum = 0;
    for (int i = 0; i < 54900; i++)
    {
        // 使用两点间距离公式 求Dot(i):（X_i,Y_i）和Dot(i+1):（X_(i+1),Y_(i+1）)的距离d
        // 将距离d放到数组DotDistance的相应位置。

        DotDistance[i] = sqrt(pow(dotArr_x[i + 1] - dotArr_x[i], 2) + pow(dotArr_y[i + 1] - dotArr_y[i], 2));
        // printf("lineNumber:%d, %lf\n ", i + 1, DotDistance[i]);
    }
    // Kids want to know the sum.
    for (int p = 0; p < 54900; p++)
    {
        sum += DotDistance[p];
    }
    return sum;
}
// 看transcend函数, 龙头序号点
void printArr_int(int arr[])
{
    int size = 300; // 计算数组中元素的数量
    printf("The elements in the array are:\n");
    for (int i = 0; i < size; i++)
    {
        printf("line%d:  %d \n", i, arr[i]); // 打印当前元素
    }
    printf("\n"); // 打印换行符
}

//
void findothers_1(double HeadLoc_x[], double HeadLoc_y[])
{
    double OthersLocation_x[222] = {0};
    double OthersLocation_y[222] = {0};

    int t = 0;
    while (t < 2)
    {

        {
            for (int s = 1; s < 2860; s++)
            {

                double distance_ = sqrt(pow(8.8 - HeadLoc_x[t], 2) + pow((double)(s) / 1000 - HeadLoc_y[t], 2));

                if (distance_ >= LongBar)
                {
                    OthersLocation_x[0] = 8.8;
                    OthersLocation_y[0] = (double)(s - 1) / 1000;
                    for (int i = 1; i < 223; i++)
                    {
                        OthersLocation_x[i] = 8.8;
                        OthersLocation_y[i] = OthersLocation_y[0] + i;
                    }
                    DotPrinter(OthersLocation_x, OthersLocation_y, 222);
                    t += 1;
                    break; // 剩余person 坐标赋值完成。
                }
            }
        }
    }
}

int findindex(int startIndex, double arr_x[], double arr_y[])
{
    if (startIndex < 108)
    {
        // 找不到下一个龙身点
        return startIndex;
    }
    else
    {
        for (int i = 1; i < startIndex; i++)
        {
            double distance = sqrt(pow(arr_x[startIndex] - arr_x[startIndex - i], 2) + pow(arr_y[startIndex] - arr_y[startIndex - i], 2));
            if (distance > shortBar)
            {
                // return startIndex - 1;
                return startIndex - i;
                break;
            }
        }
    }
}

void findOthers_2(int IndexOfHead[], double DotArr_x[], double DotArr_y[])
{
    int t = 2;
    double OtherLocation_x[222] = {0};
    double OtherLocation_y[222] = {0};
    int Itr_index = 0;

    while (t < 300) // 300
    {
        // int Itr_index = 0;
        // 找到第一个跟班，返回index
        // printf("\n Index of head:%d", IndexOfHead[t]);

        for (int i = 1; i < IndexOfHead[t]; i++)
        {
            // printf("\n-----------------------------hello?------------------------------");
            // 找到第一个跟班，返回index
            double distance = sqrt(pow(DotArr_x[IndexOfHead[t]] - DotArr_x[IndexOfHead[t] - i], 2) + pow(DotArr_y[IndexOfHead[t]] - DotArr_y[IndexOfHead[t] - i], 2));
            if (distance > LongBar)
            {
                Itr_index = IndexOfHead[t] - i + 1;
                OtherLocation_x[0] = DotArr_x[Itr_index];
                OtherLocation_y[0] = DotArr_y[Itr_index];

                break;
            }
        }
        // 找剩下的龙身点
        for (int i = 1; i < 222; i++)
        {

            // Itr_index = findindex_2(Itr_index,DotArr_x,DotArr_y);
            int temp = findindex(Itr_index, DotArr_x, DotArr_y);

            if (temp == Itr_index)
            {
                double offset = 0;
                printf("\n maybe we should fix some flix");
                // 法二算点坐标.算完就break
                for (int s = 1; s < 2860; s++)
                {
                    double distance__ = sqrt(pow(DotArr_x[Itr_index] - 8.8, 2) + pow(DotArr_y[Itr_index] - (double)s / 1000, 2));
                    if (distance__ > shortBar)
                    {
                        // printf("\n--------------the value of i is: %d----------------------------\n", i);
                        OtherLocation_x[i] = 8.8;
                        OtherLocation_y[i] = (double)(s - 1) / 1000;
                        offset = (double)(s - 1) / 1000;
                        break;
                        // printf("\n--------------the value of y is: %lf----------------------------\n", OtherLocation_y[i]);
                    }

                    // printf("\n--------------the value of offset is: %lf----------------------------\n", offset);

                    // for (int j = 1; j < 222 - i; j++)
                    // {
                    //     OtherLocation_x[i + j] = 8.8;
                    //     OtherLocation_y[i + j] = shortBar * j + offset;
                    // }
                    // break;
                }

                for (int j = 1; j < 222 - i; j++)
                {
                    OtherLocation_x[i + j] = 8.8;
                    OtherLocation_y[i + j] = shortBar * j + offset;
                }

                Itr_index = temp - 1; //

                break;
            }
            else
            {
                Itr_index = temp;
                OtherLocation_x[i] = DotArr_x[Itr_index];
                OtherLocation_y[i] = DotArr_y[Itr_index];
            }
        }
        printf("\n-------------------------t = %d----------------------------: ", t + 1);
        DotPrinter(OtherLocation_x, OtherLocation_y, 222);

        t++;
    }
}

int main()
{
    // 取点 创建两个点数组大小54901 double类型
    double dotArr_x[54901] = {0};
    double dotArr_y[54901] = {0};
    fillDotArr(dotArr_x, dotArr_y);
    // DotPrinter(dotArr_x, dotArr_y);
    // 求龙头位置
    // 先找到每一小段的距离,共54900段,积分加和
    double DotDistance[54900] = {0};
    // 调用fillarrdistance
    double sum1 = fillArrDistance(dotArr_x, dotArr_y, DotDistance);
    // printf("\nThe length for this spiral: %lf", sum1);     // 调试dotdistance
    // printArr_double(DotDistance);
    double HeadLocation_x[300] = {0};
    double HeadLocation_y[300] = {0};
    int IndexOfHead[300] = {0};

    findTranscend(IndexOfHead, DotDistance, dotArr_x, dotArr_y, HeadLocation_x, HeadLocation_y);
    // printArr_int(IndexOfHead);
    // DotPrinter(HeadLocation_x, HeadLocation_y,300);

    // findothers_1(HeadLocation_x, HeadLocation_y);   //调试findothers_1

    findOthers_2(IndexOfHead, dotArr_x, dotArr_y);
    // 找零界点
    // double sum = 0;
    // for(int i = 0; i < 300;i++){
    //     sum = sqrt(pow((dotArr_x[i+1]-8.8),2)+pow(dotArr_y[i+1],2));
    //     // sum = sum + DotDistance[i];

    //     if (sum > LongBar)
    //     {
    //         printf("\n The %dst distance is %lf",i,sum);

    //     }

    // }

    // 不必要的验证
    //  printf("\n distance between %d",)
}