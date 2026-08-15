#include <stdio.h>
#include <limits.h>

// 用于返回结果的结构体
typedef struct
{
    int left;  // 左边界索引
    int right; // 右边界索引
    int sum;   // 子数组和
} SubArray;

// 查找跨越中点的最大子数组
SubArray find_max_crossing_subarray(int arr[], int low, int mid, int high)
{
    SubArray result;

    // 从 mid 向左扫描找最大和
    int left_sum = INT_MIN;
    int sum = 0;
    int max_left = mid;
    for (int i = mid; i >= low; i--)
    {
        sum += arr[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }

    // 从 mid+1 向右扫描找最大和
    int right_sum = INT_MIN;
    sum = 0;
    int max_right = mid + 1;
    for (int j = mid + 1; j <= high; j++)
    {
        sum += arr[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }

    result.left = max_left;
    result.right = max_right;
    result.sum = left_sum + right_sum;
    return result;
}

// 递归求解最大子数组（分治法）
SubArray find_maximum_subarray(int arr[], int low, int high)
{
    SubArray result;

    if (low == high)
    { // 基本情况：只有一个元素
        result.left = low;
        result.right = high;
        result.sum = arr[low];
        return result;
    }

    int mid = low + (high - low) / 2;

    SubArray left_result = find_maximum_subarray(arr, low, mid);
    SubArray right_result = find_maximum_subarray(arr, mid + 1, high);
    SubArray cross_result = find_max_crossing_subarray(arr, low, mid, high);

    // 比较三个结果，返回和最大的那个
    if (left_result.sum >= right_result.sum && left_result.sum >= cross_result.sum)
    {
        return left_result;
    }
    else if (right_result.sum >= left_result.sum && right_result.sum >= cross_result.sum)
    {
        return right_result;
    }
    else
    {
        return cross_result;
    }
}

int main()
{
    // 书中的经典示例
    int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    SubArray result = find_maximum_subarray(arr, 0, n - 1);

    printf("最大子数组：\n");
    printf("左边界索引: %d\n", result.left);
    printf("右边界索引: %d\n", result.right);
    printf("子数组和: %d\n", result.sum);
    printf("子数组元素: ");
    for (int i = result.left; i <= result.right; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}