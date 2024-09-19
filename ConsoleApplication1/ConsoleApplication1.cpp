//1 задание
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int M = 5, N = 4;
    int arr[M][N];
    int sum = 0, min_val = 20, max_val = 0;

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 21;
            sum += arr[i][j];
            if (arr[i][j] < min_val) min_val = arr[i][j];
            if (arr[i][j] > max_val) max_val = arr[i][j];
        }
    }

    double avg = sum / static_cast<double>(M * N);

    cout << "сумма: " << sum << '\n';
    cout << "среднее арифметическое: " << avg << '\n';
    cout << "минимум: " << min_val << '\n';
    cout << "максимум: " << max_val << '\n';

    return 0;
}

//2 задание
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int M = 4;
    int arr[M][M];
    int main_diag_sum = 0, sec_diag_sum = 0;

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            arr[i][j] = rand() % 21;
        }
    }

    for (int i = 0; i < M; i++) {
        main_diag_sum += arr[i][i];
        sec_diag_sum += arr[i][M - i - 1];
    }

    cout << "сумма главной диагонали: " << main_diag_sum << '\n';
    cout << "сумма побочной диагонали: " << sec_diag_sum << '\n';

    return 0;
}


//3 задание
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int M = 5, N = 4;
    int arr[M][N];
    int pos_count = 0, neg_count = 0, zero_count = 0;

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 21 - 10;
            if (arr[i][j] > 0) pos_count++;
            else if (arr[i][j] < 0) neg_count++;
            else zero_count++;
        }
    }

    cout << "положительные элементы: " << pos_count << '\n';
    cout << "отрицательные элементы: " << neg_count << '\n';
    cout << "нулевые элементі: " << zero_count << '\n';

    return 0;
}


//4 задание
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int M = 5, N = 4;
    int arr[M][N];
    int row_sum[M] = { 0 }, col_sum[N] = { 0 };

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 21;
            row_sum[i] += arr[i][j];
            col_sum[j] += arr[i][j];
        }
    }

    cout << "сумма по строкам: ";
    for (int i = 0; i < M; i++) {
        cout << row_sum[i] << " ";
    }
    cout << '\n';

    cout << "сумма по столбцам: ";
    for (int j = 0; j < N; j++) {
        cout << col_sum[j] << " ";
    }
    cout << '\n';

    return 0;
}


//5 задание
#include <iostream>
using namespace std;

int main() {
    int M = 5, N = 4;
    int arr[M][N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = (i + 1) * 10 + (j + 1);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}


//6 задание
#include <iostream>
using namespace std;

int main() {
    int M = 6, N = 4;
    int arr[M][N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 21;
        }
    }

    for (int i = 0; i < M - 1; i += 2) {
        for (int j = 0; j < N; j++) {
            swap(arr[i], arr[i + 1]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}


//7 задание
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int M = 5, N = 4;
    int arr[M][N];
    int min_val = 100, max_val = -100;
    int min_pos = -1, max_pos = -1;
    int sum = 0;

    srand(time(0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 201 - 100;
            if (arr[i][j] < min_val) {
                min_val = arr[i][j];
                min_pos = i * N + j;
            }
            if (arr[i][j] > max_val) {
                max_val = arr[i][j];
                max_pos = i * N + j;
            }
        }
    }

    if (min_pos > max_pos) swap(min_pos, max_pos);

    for (int k = min_pos + 1; k < max_pos; k++) {
        sum += arr[k / N][k % N];
    }

    cout << "сумма между мин и макс елементами: " << sum << '\n';

    return 0;
}


//8 задание
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int M = 5;
    vector<vector<int>> arr(M, vector<int>(M, 0));

    int x = M / 2, y = M / 2;
    int num = 1;
    arr[x][y] = num++;

    int dx[] = { 0, -1, 0, 1 };
    int dy[] = { -1, 0, 1, 0 };

    for (int layer = 1; layer <= M / 2; layer++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2 * layer; j++) {
                x += dx[i];
                y += dy[i];
                if (x >= 0 && x < M && y >= 0 && y < M) {
                    arr[x][y] = num++;
                }
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cout << arr[i][j] << '\n';

