#include <iostream>
#include <string>

using namespace std;

#define TRUE 1
#define FALSE 0
#define VOCUNG 10000000

struct Graph
{
    int N;       // Số lượng đỉnh của đồ thị
    int **A;     // Ma trận trọng số
};

struct Dijkstra
{
    Graph graph;
    int start;   // Đỉnh đầu
    int end;     // Đỉnh cuối
    int *truoc;  // Mảng đánh dấu đường đi
    int *dist;   // Mảng đánh dấu khoảng cách
    int *T;      // Mảng đánh dấu đỉnh đã được gán nhãn
};

// Câu 2: Cài đặt hàm Nhap để nhập vào đồ thị từ file Grap.txt, lưu vào ma trận A
void Nhap(Dijkstra &d)
{
    FILE* f = freopen("Grap.txt", "r", stdin);
    if (!f)
    {
        cout << "Khong the mo file Grap.txt!" << endl;
        return;
    }

    // Nhập số đỉnh của đồ thị
    cin >> d.graph.N;
    // Nhập đỉnh đầu và đỉnh cuối của đồ thị
    cin >> d.start >> d.end;

    // Cấp phát bộ nhớ và nhập ma trận kề
    d.graph.A = new int*[d.graph.N];
    for (int i = 0; i < d.graph.N; i++)
    {
        d.graph.A[i] = new int[d.graph.N];
        for (int j = 0; j < d.graph.N; j++)
        {
            cin >> d.graph.A[i][j];
            if (d.graph.A[i][j] == 0) 
                d.graph.A[i][j] = VOCUNG;
        }
    }

    fclose(f);
}

// Câu 3: Cài đặt hàm HienThi để hiển thị đồ thị vừa nhập ra màn hình
void HienThi(Dijkstra d)
{
    cout << "Do thi vua nhap la:" << endl;
    cout << "- So dinh cua do thi: " << d.graph.N << endl;
    cout << "- Ma tran trong so cua do thi:" << endl;
    for (int i = 0; i < d.graph.N; i++)
    {
        for (int j = 0; j < d.graph.N; j++)
        {
            if (d.graph.A[i][j] == VOCUNG)
                cout << 0 << "\t";
            else 
                cout << d.graph.A[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm lấy tên đỉnh dưới dạng V1, V2, ..., V6
string GetName(int v)
{
    return "V" + to_string(v + 1);
}

// Kiểm tra xem tập T đã chứa hết các đỉnh chưa
bool CheckFullT(Dijkstra d)
{
    for (int i = 0; i < d.graph.N; i++)
    {
        if (!d.T[i]) return false;
    }
    return true;
}

// Câu 4: Cài đặt thuật toán tìm đường đi ngắn nhất giữa 2 đỉnh bất kỳ u và v
void TimDuongDiNganNhat(Dijkstra &d, int u, int v)
{
    d.start = u;
    d.end = v;

    d.truoc = new int[d.graph.N];
    d.dist = new int[d.graph.N];
    d.T = new int[d.graph.N];

    // Khởi tạo
    for (int i = 0; i < d.graph.N; i++)
    {
        d.dist[i] = VOCUNG;
        d.truoc[i] = -1;
        d.T[i] = FALSE;
    }
    d.dist[d.start] = 0;

    // Vòng lặp thuật toán Dijkstra
    while (!CheckFullT(d))
    {
        int curr = -1;
        int minp = VOCUNG;

        for (int i = 0; i < d.graph.N; i++)
        {
            if (!d.T[i] && d.dist[i] < minp)
            {
                curr = i;
                minp = d.dist[i];
            }
        }

        if (curr == -1 || minp == VOCUNG) break; // Đồ thị không liên thông

        d.T[curr] = TRUE;

        for (int i = 0; i < d.graph.N; i++)
        {
            if (!d.T[i] && d.graph.A[curr][i] != VOCUNG
                && (d.dist[curr] + d.graph.A[curr][i] < d.dist[i]))
            {
                d.dist[i] = d.dist[curr] + d.graph.A[curr][i];
                d.truoc[i] = curr;
            }
        }
    }

    // Hiển thị kết quả đường đi tìm được
    int dinhcuoi = d.end;
    cout << "\nDuong di ngan nhat tu " << GetName(d.start)
         << " den " << GetName(dinhcuoi) << " la:" << endl;
    
    if (d.dist[dinhcuoi] == VOCUNG)
    {
        cout << "Khong co duong di!" << endl;
        return;
    }

    cout << GetName(dinhcuoi);
    int p = d.truoc[dinhcuoi];
    while (p != -1)
    {
        cout << " <= " << GetName(p);
        if (p == d.start) break;
        p = d.truoc[p];
    }
    cout << endl << "Do dai duong di la : " << d.dist[dinhcuoi] << endl;
}

// Câu 5: Cài đặt hàm main()
int main()
{
    Dijkstra d;

    // 1. Gọi hàm Nhập để nhập đồ thị từ file
    Nhap(d);

    // 2. Gọi hàm Hiển thị để hiển thị đồ thị ra màn hình
    HienThi(d);

    // 3. Gọi hàm Tìm đường đi để tìm đường đi từ đỉnh V1 (chỉ số 0) đến V6 (chỉ số 5)
    TimDuongDiNganNhat(d, 0, 5);

    // Giải phóng bộ nhớ động
    for (int i = 0; i < d.graph.N; ++i) {
        delete[] d.graph.A[i];
    }
    delete[] d.graph.A;
    delete[] d.truoc;
    delete[] d.dist;
    delete[] d.T;

    return 0;
}