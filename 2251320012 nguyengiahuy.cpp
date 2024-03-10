#include <iostream>
#include <iomanip>

using namespace std;

struct QuanAo {
    int ma;
    string ten;
    string trangThai;
    string size;
    string mauSac;
    string nguonGoc;
    int soLuong;
    int donGia;
    int thanhTien;
};

struct Node {
    QuanAo data;
    Node* trai;
    Node* phai;
};

class CuaHangQuanAo {
public:
    Node* goc;

    Node* taoNode(const QuanAo& quanAo) {
        Node* nodeMoi = new Node;
        nodeMoi->data = quanAo;
        nodeMoi->trai = nodeMoi->phai = NULL;
        return nodeMoi;
    }

    Node* them(Node* goc, const QuanAo& quanAo) {
        if (goc == NULL) {
            return taoNode(quanAo);
        }

        if (quanAo.ma < goc->data.ma) {
            goc->trai = them(goc->trai, quanAo);
        } else if (quanAo.ma > goc->data.ma) {
            goc->phai = them(goc->phai, quanAo);
        }

        return goc;
    }

    void duyetTheoThuTu(Node* goc) {
        if (goc != NULL) {
            duyetTheoThuTu(goc->trai);
            hienThiQuanAo(goc->data);
            duyetTheoThuTu(goc->phai);
        }
    }

    void hienThiQuanAo(const QuanAo& quanAo) {
        cout << "Ma: " << quanAo.ma << endl;
        cout << "Ten: " << quanAo.ten << endl;
        cout << "Trang thai: " << quanAo.trangThai << endl;
        cout << "Size: " << quanAo.size << endl;
        cout << "Mau sac: " << quanAo.mauSac << endl;
        cout << "Nguon goc: " << quanAo.nguonGoc << endl;
        cout << "So luong: " << quanAo.soLuong << endl;
        cout << "Don gia: " << quanAo.donGia << endl;
        cout << "Thanh tien: " << quanAo.thanhTien << endl;
        cout << "------------------------" << endl;
    }

    Node* tim(Node* goc, int ma) {
        if (goc == NULL || goc->data.ma == ma) {
            return goc;
        }

        if (ma < goc->data.ma) {
            return tim(goc->trai, ma);
        } else {
            return tim(goc->phai, ma);
        }
    }

    Node* timMin(Node* goc) {
        while (goc->trai != NULL) {
            goc = goc->trai;
        }
        return goc;
    }

    Node* xoa(Node* goc, int ma) {
        if (goc == NULL) {
            return goc;
        }

        if (ma < goc->data.ma) {
            goc->trai = xoa(goc->trai, ma);
        } else if (ma > goc->data.ma) {
            goc->phai = xoa(goc->phai, ma);
        } else {
            if (goc->trai == NULL) {
                Node* temp = goc->phai;
                delete goc;
                return temp;
            } else if (goc->phai == NULL) {
                Node* temp = goc->trai;
                delete goc;
                return temp;
            }

            Node* temp = timMin(goc->phai);
            goc->data = temp->data;
            goc->phai = xoa(goc->phai, temp->data.ma);
        }

        return goc;
    }

public:
    CuaHangQuanAo() : goc(NULL) {}

    void themQuanAo() {
        QuanAo quanAoMoi;
        cout << "Nhap thong tin quan ao:" << endl;
        cout << "Ma: ";
        cin >> quanAoMoi.ma;
        cout << "Ten: ";
        cin.ignore(); 
        getline(cin, quanAoMoi.ten);
        cout << "Trang thai (con/het): ";
        cin >> quanAoMoi.trangThai;
        cout << "Size: ";
        cin >> quanAoMoi.size;
        cout << "Mau sac: ";
        cin.ignore(); 
        getline(cin, quanAoMoi.mauSac);
        cout << "Nguon goc: ";
        cin.ignore(); 
        getline(cin, quanAoMoi.nguonGoc);
        cout << "So luong: ";
        cin >> quanAoMoi.soLuong;
        cout << "Don gia: ";
        cin >> quanAoMoi.donGia;
        quanAoMoi.thanhTien = quanAoMoi.soLuong * quanAoMoi.donGia;

        goc = them(goc, quanAoMoi);
        cout << "Quan ao da duoc them thanh cong!" << endl;
    }

    void hienThiDanhSachQuanAo() {
        if (goc == NULL) {
            cout << "Danh sach quan ao trong!" << endl;
        } else {
            cout << "Danh sach quan ao:" << endl;
            duyetTheoThuTu(goc);
        }
    }

    int demQuanAo() {
        
        return demNode(goc);
    }

    int demNode(Node* goc) {
        if (goc == NULL) {
            return 0;
        }

        return 1 + demNode(goc->trai) + demNode(goc->phai);
    }

    QuanAo timQuanAo(int ma) {
        Node* node = tim(goc, ma);
        if (node != NULL) {
            return node->data;
        } else {
            QuanAo quanAoKhongTimThay;
            quanAoKhongTimThay.ma = -1; 
            return quanAoKhongTimThay;
        }
    }

    void hienThiQuanAoCon() {
        hienThiQuanAoCon(goc);
    }

    void hienThiQuanAoCon(Node* goc) {
        if (goc != NULL) {
            hienThiQuanAoCon(goc->trai);
            if (goc->data.trangThai == "con") {
                hienThiQuanAo(goc->data);
            }
            hienThiQuanAoCon(goc->phai);
        }
    }

    void xoaQuanAoHetHang() {
        xoaQuanAoHetHang(goc);
    }

    void xoaQuanAoHetHang(Node* goc) {
        if (goc != NULL) {
            xoaQuanAoHetHang(goc->trai);
            if (goc->data.trangThai == "het") {
                goc = xoa(goc, goc->data.ma);
            }
            xoaQuanAoHetHang(goc->phai);
        }
    }
};

int main() {
    CuaHangQuanAo cuaHang;

    int soLuongQuanAo;
    cout << "Nhap so luong quan ao: ";
    cin >> soLuongQuanAo;

    for (int i = 0; i < soLuongQuanAo; ++i) {
        cout << "Nhap thong tin cho quan ao thu: " << i + 1 << endl;
        cuaHang.themQuanAo();
    }

    cuaHang.hienThiDanhSachQuanAo();

    int dem = cuaHang.demQuanAo();
    cout << "So luong quan ao trong danh sach: " << dem << endl;

    int maTimKiem;
    cout << "Nhap ma quan ao can tim: ";
    cin >> maTimKiem;

    QuanAo quanAoTimThay = cuaHang.timQuanAo(maTimKiem);
    if (quanAoTimThay.ma != -1) {
        cout << "Thong tin quan ao duoc tim thay:" << endl;
        cuaHang.hienThiQuanAo(quanAoTimThay);
    } else {
        cout << "Khong tim thay quan ao co ma " << maTimKiem << endl;
    }

    cout << "Thong tin quan ao con lai:" << endl;
    cuaHang.hienThiQuanAoCon();

    cuaHang.xoaQuanAoHetHang();

    cout << "Danh sách quan ao sau khi xoa ds het hang:" << endl;
    cuaHang.hienThiDanhSachQuanAo();

    return 0;
}

