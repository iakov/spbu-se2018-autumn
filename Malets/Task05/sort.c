#include <string.h>

#include "sort.h"

#define LESS   0x1
#define EQUAL  0x2
#define LARGER 0x4

#define isLess( line1, line2 )   (compare(line1, line2) & LESS)
#define isLarger( line1, line2 ) (compare(line1, line2) & LARGER)

static void swapLines( Line* line1, Line* line2 )
{
    Line temp = *line1;
    *line1 = *line2;
    *line2 = temp;
}

static int64_t compare( Line* line1, Line* line2 )
{
    static int64_t priority[256] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,

        // '0' - '9'
        0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B,

        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,

        // 'A' - 'Z'
        0x4C, 0x4E, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x64,
        0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E,

        0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,

        // 'a' - 'z'
        0x4D, 0x4F, 0x51, 0x53, 0x55, 0x57, 0x59, 0x5B, 0x5D, 0x5F, 0x61, 0x63, 0x65,
        0x67, 0x69, 0x6B, 0x6D, 0x6F, 0x71, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7F,

        0x3D, 0x3E, 0x3F, 0x40, 0x41,
    };

    uint64_t comparsionSize = line1->size;
    if (comparsionSize > line2->size)
        comparsionSize = line2->size;

    for (uint64_t i = 0; i < comparsionSize; i++)
    {
        if (line1->begin[i] != line2->begin[i])
        {
            if (priority[line1->begin[i]] < priority[line2->begin[i]])
                return LESS;

            return LARGER;
        }
    }

    if (line1->size < line2->size)
        return LESS;

    if (line1->size > line2->size)
        return LARGER;

    return EQUAL;
}

static void sortBubble()
{
    for (int64_t count = g_linesCount - 1; count > 0; count--)
    {
        for (int64_t i = 0; i < count; i++)
        {
            if (isLarger(g_lines + i, g_lines + i + 1))
                swapLines(g_lines + i, g_lines + i + 1);
        }
    }
}

static void sortInsertion()
{
    for (int64_t i = 1; i < g_linesCount; i++)
    {
        int64_t j = i - 1;

        while (j >= 0 && isLess(g_lines + i, g_lines + j))
            j--;

        j++;

        Line line = g_lines[i];

        for (int64_t k = i - 1; k >= j; k--)
            g_lines[k + 1] = g_lines[k];

        g_lines[j] = line;
    }
}

static void sortQuickRec( int64_t first, int64_t last )
{
    if (first >= last)
        return;

    int64_t pivot = first;

    for (int64_t i = first; i < last; i++)
    {
        if (isLess(g_lines + i, g_lines + last))
        {
            swapLines(g_lines + i, g_lines + pivot);
            pivot++;
        }
    }

    swapLines(g_lines + last, g_lines + pivot);

    sortQuickRec(first, pivot - 1);
    sortQuickRec(pivot + 1, last);
}

static void sortQuick()
{
    sortQuickRec(0, g_linesCount - 1);
}

static void sortMerge()
{
    Line* sorted = allocateMemory(sizeof(Line) * g_linesCount);

    for (int64_t blockSize = 1; blockSize < g_linesCount; blockSize <<= 1)
    {
        int64_t doubleSize = blockSize << 1;

        for (int64_t offset = 0; offset < g_linesCount - blockSize; offset += doubleSize)
        {
            int64_t leftSize = blockSize;
            int64_t rightSize = blockSize;

            if (offset + leftSize + rightSize > g_linesCount)
                rightSize = g_linesCount - leftSize - offset;

            Line* left = g_lines + offset;
            Line* right = left + leftSize;

            int64_t leftIndex = 0;
            int64_t rightIndex = 0;

            while (leftIndex < leftSize && rightIndex < rightSize)
            {
                if (isLess(left + leftIndex, right + rightIndex))
                {
                    sorted[leftIndex + rightIndex] = left[leftIndex];
                    leftIndex++;
                }
                else
                {
                    sorted[leftIndex + rightIndex] = right[rightIndex];
                    rightIndex++;
                }
            }

            memcpy(sorted + rightSize + leftIndex, left + leftIndex,
                   sizeof(Line) * (leftSize - leftIndex));

            memcpy(sorted + leftSize + rightIndex, right + rightIndex,
                   sizeof(Line) * (rightSize - rightIndex));

            memcpy(left, sorted, sizeof(Line) * (leftSize + rightSize));
        }
    }

    freeMemory(sorted);
}

static void correctHeap( int64_t index, int64_t count )
{
    int64_t middle = (count >> 1) - 1;
    int64_t left;
    int64_t right;
    int64_t max;

    while (index < middle)
    {
        max = index;
        left = (index << 1) + 1;
        right = left + 1;

        if (isLess(g_lines + max, g_lines + left))
            max = left;

        if (isLess(g_lines + max, g_lines + right))
            max = right;

        if (max == index)
            return;

        swapLines(g_lines + max, g_lines + index);

        index = max;
    }

    if (index == middle)
    {
        max = index;
        left = (index << 1) + 1;
        right = left + 1;

        if (isLess(g_lines + max, g_lines + left))
            max = left;

        if (count & 0x1 && isLess(g_lines + max, g_lines + right))
            max = right;

        if (max != index)
            swapLines(g_lines + max, g_lines + index);
    }
}

static void sortHeap()
{
    for (int64_t i = (g_linesCount >> 1) - 1; i >= 0; i--)
        correctHeap(i, g_linesCount);

    for (int64_t i = g_linesCount - 1; i > 0; i--)
    {
        swapLines(g_lines, g_lines + i);
        correctHeap(0, i);
    }
}

#define BUBBLE_ID_LOW     0x5c58b665
#define BUBBLE_ID_HIGH    0x317
#define INSERTION_ID_LOW  0x2e9a77ee
#define INSERTION_ID_HIGH 0x69ddcf2f
#define QUICK_ID_LOW      0x1eba71eb
#define QUICK_ID_HIGH     0x7
#define MERGE_ID_LOW      0xdcbcb3e5
#define MERGE_ID_HIGH     0x6
#define HEAP_ID_LOW       0xd1970f0
#define HEAP_ID_HIGH      0x0
#define RADIX_ID_LOW      0x2c3934f8
#define RADIX_ID_HIGH     0x7

SortingMethod getSortingMethod( uint64_t id )
{
    uint64_t lowPart = id & 0xFFFFFFFF;
    uint64_t highPart = id >> 32;

    switch (lowPart)
    {
        case BUBBLE_ID_LOW:
            if (highPart == BUBBLE_ID_HIGH)
                return sortBubble;
            return NULL;
        case INSERTION_ID_LOW:
            if (highPart == INSERTION_ID_HIGH)
                return sortInsertion;
            return NULL;
        case QUICK_ID_LOW:
            if (highPart == QUICK_ID_HIGH)
                return sortQuick;
            return NULL;
        case MERGE_ID_LOW:
            if (highPart == MERGE_ID_HIGH)
                return sortMerge;
            return NULL;
        case HEAP_ID_LOW:
        case RADIX_ID_LOW:
            if (highPart == HEAP_ID_HIGH || highPart == RADIX_ID_HIGH)
                return sortHeap;
            return NULL;
        default:
            return NULL;
    }
}
