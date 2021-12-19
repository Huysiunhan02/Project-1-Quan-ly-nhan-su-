/*
 ==========================Do An 1==========================
|Name	 : Ung dung quan ly nhan su chi nhanh ngan hang     |
|Password: quanghuy										    |
|														    |
|Coder	 : Bui Quang Huy								    |
|ID		 : 10120143										    |
|Class	 : 101203										    |
 ===========================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define MAX 30 //so luong nhan vien toi da

//===============Cau truc du lieu==================

//Cấu trúc ngày
typedef struct{
	int ngay,thang,nam;
}Date;

//Chuc vu
typedef struct {
	char TenCV[30],MaCV[6];
	float HSLuong;
	int Thuong, SL;
}CV;


typedef struct {
	char MaNV[6],HoTen[30],GioiTinh[5],QueQuan[20];
	char MaCV[6];
	Date NgaySinh;
}NhanVien;

typedef struct{
	char Manv[6];
	char Sang[2], Chieu[2];
}Cong;

//Danh sach cong
typedef struct{
	Date Ngay;
	Cong nv[MAX];
}DSCong;

typedef struct{
	char Manv[6];
	int Tien;
}Luong;

//Danh sach luong
typedef struct{
	int thang,nam;
	Luong nv[MAX];
}DSLuong;

typedef struct{
	float NLam,NNghi,TLNghi,LuongTB;
}ThongKe;


//Cac bien toan cuc

//vi tri hien thi
int x=50, y=10; 
int luong1c = 200000;//muc luong mac dinh 1cong
int slnv=0;//so luong nhan vien hien tai
int slcv=0;//so luong chuc vu hien tai
int songay=0;//so ngay cham cong hien tai
int sothang=0;//so thang da tinh luong hien tai

//ket thuc 
void close(){
	printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tCoder by Quang Huy\n\n\n");
}
//===================================================
//di chuyen vi tri con tro trong man hinh consle
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
//tao 1 khoi hien thi 
void box(int hang, int cot, int x, int y)//tham so vao lan luot la so hang, so cot, vi tri toa do x,y
{
     int i,j;
    for(i=0; i<hang+4; i++){
        for(j=0; j<cot; j++){
            if (i==0 || i==2 || i==hang+3){
                if (j==0 || j==cot-1) {gotoxy(x+j,y+i);printf("+");}
                else {gotoxy(x+j,y+i); printf("-");}
            }
            else {
                if (j==0 || j==cot-1) {gotoxy(x+j,y+i); printf("|");}
                else {gotoxy(x+j,y+i); printf(" ");}
            }
        }
        gotoxy(x+j,y+i);printf("\n");
    }
}

//=============loading

void fordelay(int j){   
	int i,k;
    for(i=0;i<j;i++)
        k=i;
}
void loading(){
	int i;
	for(i=0;i<=6;i++) {
        fordelay(50000000);
        printf(".");
    }
}

//=======================================================
void menu();
void ThongTin();
void Docfilecv();

//kiem tra co tim thay nhan vien hay khong
//tra ve: 1 neu tim thay, 0 neu khong tim thay
int scanttnv(NhanVien *ds, int slnv, char ma[10]){
	int i,timthay=0;
	for (i=0; i<slnv; i++){
	 	char *t =strstr(ds[i].MaNV,ma);
		if (t){
			timthay++;
			break;
		}
	}
	return timthay;
}

//Doc file nhan vien
void Docfilenv(NhanVien *ds,int *slnv){
	FILE *f =fopen("Nhanvien.txt","r");
	int n =0;
	if(f){
		for (;;){
			NhanVien nv;
			fscanf(f,"%15s %25[^\n] %02d/%02d/%4d\t  %15s %15[^\n] %15s\n",nv.MaNV,nv.HoTen,&nv.NgaySinh.ngay, &nv.NgaySinh.thang, &nv.NgaySinh.nam,nv.GioiTinh,nv.QueQuan,nv.MaCV);
			ds[n++]=nv;
			if(feof(f)) break;
		}
	}
	else {
		gotoxy(160,0);printf("Du lieu nhan vien chua ton tai");
	}
	fclose(f);
	*slnv=n;
}

//Them nhan vien
void Docfilecong();
void Docfileluong();
void AddNV(){
	NhanVien dsnv[MAX];
	NhanVien nvm;//nhan vien moi
	CV dscv[20];
	Docfilecv(dscv,&slcv);
	system("cls");
	if (slcv < 1) {
		gotoxy(x,y);printf("Chua co thong tin chuc vu,vui long them chuc vu ");
		getch();
		menu();
		return;
	}
	int s;//lua chon
	int n;//so luong nhan vien muon them
	int i,j;
	int count=0;
	box(6,45,x,y);
	gotoxy(1+x,1+y);printf("---------------Them nhan vien--------------");
	gotoxy(1+x,3+y);printf("Nhap so luong :  ");
	gotoxy(17+x,3+y);scanf("%d",&n);
	nhapthongtin:
	Docfilenv(dsnv,&slnv);
	box(6,45,x,y);
	gotoxy(1+x,1+y);printf("---------------Them nhan vien--------------");
	if (n>1){
		gotoxy(x+47,y+1);printf("---> | Nhan vien thu %d |",count+1);
	}
	while(1){
		gotoxy(1+x,3+y);printf("Nhap ma nhan vien (gom 5 ki tu) :      ");fflush(stdin);
		gotoxy(x+1+34, y+3);scanf("%s",nvm.MaNV);
		if (strlen(nvm.MaNV) == 5) {
			if (scanttnv(dsnv,slnv,nvm.MaNV) == 0) break;
			else {
				gotoxy(x+1,y+10);printf("\aMa nhan vien da ton tai !              ");
				gotoxy(x+1,y+11);printf("Nhan phim bat ki de tiep tuc");
				getch();
				if (count<n){
					goto nhapthongtin;
				}
				else {
					ThongTin();
					return;
				}
			}
		}
		else {
			gotoxy(x+1, y+10);printf("\aSai dinh dang,ma nhan vien gom 5 ky tu !");
		}
	}
	fflush(stdin);
	gotoxy(x+1,y+4);printf("Nhap ho va ten :                      ");
	gotoxy(x+1+17,y+4);gets(nvm.HoTen);strupr(nvm.HoTen);

	while(1){
		gotoxy(x+1, y+5);printf("Nhap ngay sinh :           ");fflush(stdin);
		gotoxy(x+1+17, y+5);scanf("%d/%d/%d",&nvm.NgaySinh.ngay, &nvm.NgaySinh.thang, &nvm.NgaySinh.nam);
		if ((nvm.NgaySinh.ngay>=1&&nvm.NgaySinh.ngay<=31)&&(nvm.NgaySinh.thang>=1&&nvm.NgaySinh.thang<=12)&&(nvm.NgaySinh.nam>=1940&&nvm.NgaySinh.nam<=2010) ) break;
		else{
			gotoxy(x+1,y+10);printf("\a        Khong hop le          ");
		}
	}
	while (1){
		gotoxy(x+1, y+6);printf("Nhap gioi tinh :     ");
		gotoxy(x+1+17, y+6);scanf("%s",&nvm.GioiTinh);
		strupr(nvm.GioiTinh);
		if ( strcmp(nvm.GioiTinh, "NAM")==0 || strcmp(nvm.GioiTinh, "NU")==0 ) break;
		else {
			gotoxy(x+1,y+10);printf("\a       Khong hop le           ");
		}
	}

	gotoxy(x+1, y+7);printf("Nhap que quan :          ");
	getchar();
	gotoxy(x+1+16, y+7);gets(nvm.QueQuan);strupr(nvm.QueQuan);
	while (1){ //kiem tra ma chuc vu
		gotoxy(x+1, y+8);printf("Nhap ma chuc vu (gom 5 ki tu) :      ");
		gotoxy(x+1+32, y+8);scanf("%s",&nvm.MaCV);
		if(strlen(nvm.MaCV)==5) { //kiem tra do dai ki tu
			int tontai=0;
			int isl=0;
			for (i=0; i<slcv; i++){
				if (strcmp(nvm.MaCV, dscv[i].MaCV)==0) { //kiem tra ma chuc vu ton tai hay chua
					tontai=1;
					break;
				}
			}
			for (j=0; j<slnv; j++){ //kiem tra chuc vu da du so luong chua
				if(strcmp(dsnv[j].MaCV, dscv[i].MaCV)==0) isl++;
			}
			if (tontai == 1 && isl < dscv[i].SL) break;
			else if (tontai == 1) { gotoxy(x+1,y+10); printf("\aChuc vu nay da du nhan vien");}
			else {
				gotoxy(x+1,y+10);printf("\a  Chuc vu khong ton tai  ");
			}
		}
		else {
			gotoxy(x+1,y+10);printf("\a     Khong hop le    ");
		}
	}
	count++;
	box(1,107,x,y+15);
	gotoxy(x+1, y+1+15);printf("%-15s|%-25s|%-15s|%-15s|%-15s|%-15s","MaNV","Ho ten","Ngay sinh","Gioi tinh","Que quan","Ma CV");
	gotoxy(x+1, y+3+15);printf("%-15s|%-25s|%02d/%02d/%4d     |%-15s|%-15s|%-15s",nvm.MaNV,nvm.HoTen,nvm.NgaySinh.ngay, nvm.NgaySinh.thang, nvm.NgaySinh.nam,nvm.GioiTinh,nvm.QueQuan,nvm.MaCV);
	xacnhan:
	gotoxy(x+1,y+5+15);printf("Xac nhan them (1.Co  0.Khong):    ");
	gotoxy(x+1+31,y+20);scanf("%d",&s);
	if (s==0){
		if (count<n) {
			system("cls");
			goto nhapthongtin;
		}
		else{
			menu();
			return;
		}
	}
	else if (s==1){ //luu du lieu vao tep
		FILE *fnv=fopen("Nhanvien.txt","a+");
		fprintf(fnv,"%-15s %-25s %02d/%02d/%4d\t  %-15s %-15s %-15s\n",nvm.MaNV,nvm.HoTen,nvm.NgaySinh.ngay, nvm.NgaySinh.thang, nvm.NgaySinh.nam,nvm.GioiTinh,nvm.QueQuan,nvm.MaCV);
		fclose(fnv);
		//Khi them nhan vien moi neu da co du lieu cham cong truoc do thi them du lieu cong cua nv moi
		DSCong dscc[30];
		Docfilecong(dscc,&songay);
		if (songay>0){
			FILE *fc = fopen("Suacong.txt","w");
			for (i =0; i<songay; i++){
				fprintf(fc,"%02d/%02d/%4d\n", dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
				strcpy(dscc[i].nv[slnv].Manv, nvm.MaNV);//tai day slnv chua tang them 1 nen index nhan vien moi = slnv
				for (j=0; j < slnv+1; j++)
				{
					if (j==slnv){
						fprintf(fc,"%-15s %-10s %-10s\n", dscc[i].nv[j].Manv, "0", "0");fflush(stdin);
					}
					else {
						fprintf(fc,"%-15s %-10s %-10s\n", dscc[i].nv[j].Manv, dscc[i].nv[j].Sang, dscc[i].nv[j].Chieu);fflush(stdin);
					}
				}
			}
			fclose(fc);
			remove("Chamcong.txt");
			rename("Suacong.txt","Chamcong.txt");
		}
		DSLuong dsluong[12];
		Docfileluong(dsluong,&sothang);
		if (sothang>0){
			FILE *fluong = fopen("Sualuong.txt","w");
			for (i=0; i<sothang; i++){
				fprintf(fluong,"%02d/%4d\n",dsluong[i].thang, dsluong[i].nam);
				strcpy(dsluong[i].nv[slnv].Manv, nvm.MaNV);
				for (j=0; j<slnv+1; j++){
					if (j==slnv) {
						fprintf(fluong,"%-10s %-15d\n",dsluong[i].nv[j].Manv, 0);
					}
					else {
						fprintf(fluong,"%-10s %-15d\n",dsluong[i].nv[j].Manv, dsluong[i].nv[j].Tien);
					}
				}
			}
			fclose(fluong);
			remove("Bangluong.txt");
			rename("Sualuong.txt","Bangluong.txt");
		}
		gotoxy(x+1,y+23);printf("Da luu");
	}
	else{
		gotoxy(x+1,y+23);printf("\aKhong hop le !");
		goto xacnhan;
	}
	if (count < n) {
		system("cls");
	  	goto nhapthongtin;
	}
	xacnhan2:
	gotoxy(x+1,y+22);
	printf("Chon 1 de quay ve menu,chon 2 de thoat :   ");
	scanf("%d",&s);
	if (s==1) menu();
	else if (s==2) close();
	else{
		gotoxy(x+1,y+23);printf("\aKhong hop le !");
		goto xacnhan2;
	}
}

//Cap nhat thong tin nhan vien
void UpdNV(){
	NhanVien nvm;
	NhanVien dsnv[MAX];
	Docfilenv(dsnv,&slnv);
	int s, i;
	system("cls");
	printf("\t\t\t---------Cap nhat thong tin--------\n");
	printf("\n\n");
	
	nhap://nhap ma nhan vien
	while(1){
		printf("\t\t\tNhap ma nhan vien : ");fflush(stdin);
		gets(nvm.MaNV);
		if (strlen(nvm.MaNV) == 5) {
			int timthay=0;
			for (i=0; i<slnv; i++){
	 			char *t =strstr(dsnv[i].MaNV,nvm.MaNV);
				if (t){
					timthay=1;
					break;
				}
			}
			if (timthay == 0){
				printf("\n\t\t\tMa nhan vien khong ton tai");
				goto nhap;
			}
			else break;
		}
		else printf("Sai dinh dang,ma nhan vien gom 5 ky tu !\n\n");
	}
	chon://nhap lua chon
	printf("\n");
	printf("\t\t\t1.Ten nhan vien\n");
	printf("\t\t\t2.Ngay sinh\n");
	printf("\t\t\t3.Gioi tinh\n");
	printf("\t\t\t4.Que quan\n");
	printf("\t\t\t5.Ma chuc vu \n");
	printf("\t\t\t6.Cap nhat tat ca\n");
	printf("\n\n");

	printf("\t\t\tChon thong tin can cap nhat : ");
	scanf("%d",&s);
	if (s==1){
		getchar();
		printf("\nNhap ho va ten : ");
		gets(nvm.HoTen);
		strcpy(dsnv[i].HoTen, nvm.HoTen);	
	}
	else if (s==2){
		printf("\nNhap ngay sinh :");fflush(stdin);
		scanf("%d/%d/%d",&nvm.NgaySinh.ngay, &nvm.NgaySinh.thang, &nvm.NgaySinh.nam);
		dsnv[i].NgaySinh.ngay=nvm.NgaySinh.ngay;
		dsnv[i].NgaySinh.thang=nvm.NgaySinh.thang;
		dsnv[i].NgaySinh.nam=nvm.NgaySinh.nam;
	}
	else if (s==3){
		printf("\nNhap gioi tinh :");
		scanf("%s",&nvm.GioiTinh);
		strcpy(dsnv[i].GioiTinh,nvm.GioiTinh);
	}
	else if (s==4){
		printf("\nNhap que quan : ");
		getchar();
		gets(nvm.QueQuan);
		strcpy(dsnv[i].QueQuan, nvm.QueQuan);
	}
	else if (s==5){
		printf("\nNhap ma chuc vu : ");
		scanf("%s",&nvm.MaCV);
		strcpy(dsnv[i].MaCV,nvm.MaCV);
	}
	else if (s==6){
		getchar();
		printf("\nNhap ho va ten : ");
		gets(nvm.HoTen);
		strcpy(dsnv[i].HoTen, nvm.HoTen);
		printf("\nNhap ngay sinh :");fflush(stdin);
		scanf("%d/%d/%d",&nvm.NgaySinh.ngay, &nvm.NgaySinh.thang, &nvm.NgaySinh.nam);
		dsnv[i].NgaySinh.ngay=nvm.NgaySinh.ngay;
		dsnv[i].NgaySinh.thang=nvm.NgaySinh.thang;
		dsnv[i].NgaySinh.nam=nvm.NgaySinh.nam;
		printf("\nNhap gioi tinh :");
		scanf("%s",&nvm.GioiTinh);
		strcpy(dsnv[i].GioiTinh,nvm.GioiTinh);
		printf("\nNhap que quan : ");
		getchar();
		gets(nvm.QueQuan);
		strcpy(dsnv[i].QueQuan, nvm.QueQuan);
		printf("\nNhap ma chuc vu : ");
		scanf("%s",&nvm.MaCV);
		strcpy(dsnv[i].MaCV,nvm.MaCV);
	}
	else{
		printf("Nhap sai !\n");
		goto chon;
	}
	
	printf("\n\n");
	printf("Dang doi ");
	printf("\n");
	box(1,107,x,y+15);
	gotoxy(x+1, y+1+15);printf("%-15s|%-25s|%-15s|%-15s|%-15s|%-15s","MaNV","Ho ten","Ngay sinh","Gioi tinh","Que quan","Ma CV");
	gotoxy(x+1, y+3+15);printf("%-15s|%-25s|%02d/%02d/%4d     |%-15s|%-15s|%-15s",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
	xacnhan:
	printf("\n\n\nXac nhan luu  1.Co  2.Khong	:");
	scanf("%d",&s);
	if (s==2){
		menu();
	}
	else if (s==1){
		getchar();
		FILE *fnvm=fopen("updnv.txt","w");
		for(i=0;i<slnv;i++){
			fprintf(fnvm,"%-15s %-25s %02d/%02d/%4d\t  %-15s %-15s %-15s\n",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
		}
		fclose(fnvm);
		remove("Nhanvien.txt");
		rename("updnv.txt","Nhanvien.txt");
		printf("\n\t\t\tThanh cong");
		l:
		printf("\nChon 1 de quay ve menu,chon 2 de thoat :");
		scanf("%d",&s);
		if (s==1) menu();
		else if (s==2) exit(0);
		else{
			printf("\nKhong hop le !");
			goto l;
		}
	}
	else{
		printf("Khong hop le !");
		goto xacnhan;
	}
}
//Tim kiem nhan vien
SearchNV(){
	NhanVien dsnv[MAX];
	int s,i ,timthay=0;
	Docfilenv(dsnv,&slnv);
	NhanVien nvm;//nhan vien nhap vao
	while(1){
		printf("\t\t\tNhap ma nhan vien : ");fflush(stdin);
		gets(nvm.MaNV);
		if (strlen(nvm.MaNV) == 5) {
			for (i=0; i<slnv; i++){
	 			char *t =strstr(dsnv[i].MaNV,nvm.MaNV);
				if (t){
					timthay=1;
					break;
				}
			}
			break;
		}
		else printf("Sai dinh dang,ma nhan vien gom 5 ky tu !\n\n");
	}
	if (timthay==1){
		box(1,107,x,y+15);
		gotoxy(x+1, y+1+15);printf("%-15s|%-25s|%-15s|%-15s|%-15s|%-15s","MaNV","Ho ten","Ngay sinh","Gioi tinh","Que quan","Ma CV");
		gotoxy(x+1, y+3+15);printf("%-15s|%-25s|%02d/%02d/%4d     |%-15s|%-15s|%-15s",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
		printf("\n1.Tiep tuc tim \t 2.Tro ve \t 0.Thoat \nNhap lua chon :");
		
		while(1){
			scanf("%d",&s);
			if (s==1 || s==2 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai\nNhap lua chon : ");
		}
		if (s==1) SearchNV();
		else if (s==2) ThongTin();
		else exit(0);
	}
	else {
		printf("\n\t\t\tKhong co trong danh sach");
		printf("\n1.Tiep tuc tim \t 2.Tro ve \t 0.Thoat \nNhap lua chon :");
		
		while(1){
			scanf("%d",&s);
			if (s==1 || s==2 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai\nNhap lua chon : ");
		}
		if (s==1) SearchNV();
		else if (s==2) ThongTin();
		else exit(0);
	}
}
//Xoa nhan vien
void DeleteNV(){
	NhanVien dsnv[MAX];
	int s, i, j, inv , timthay=0;
	Docfilenv(dsnv,&slnv);
	NhanVien nvm;
	while(1){
		printf("\t\t\tNhap ma nhan vien : ");fflush(stdin);
		gets(nvm.MaNV);
		if (strlen(nvm.MaNV) == 5) {
			for (i=0; i<slnv; i++){
	 			char *t =strstr(dsnv[i].MaNV,nvm.MaNV);
				if (t){
					timthay=1;
					break;
				}
			}
			break;
		}
		else printf("Sai dinh dang,ma nhan vien gom 5 ky tu !\n\n");
	}
	inv=i;
	if (timthay==1){
		box(1,107,x,y+15);
		gotoxy(x+1, y+1+15);printf("%-15s|%-25s|%-15s|%-15s|%-15s|%-15s","MaNV","Ho ten","Ngay sinh","Gioi tinh","Que quan","Ma CV");
		gotoxy(x+1, y+3+15);printf("%-15s|%-25s|%02d/%02d/%4d     |%-15s|%-15s|%-15s",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
		printf("\nXac nhan xoa ? ");
		printf("\n1.Dong y \t 0.Khong \t  \nNhap lua chon :");	
		while(1){
			scanf("%d",&s);
			if (s==1 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai\nNhap lua chon : ");
		}
		if (s==1) {
			FILE *fnvm=fopen("updnv.txt","w");
			for(i=0;i<slnv;i++){
				if (i==inv) continue;
				fprintf(fnvm,"%-15s %-25s %02d/%02d/%4d\t  %-15s %-15s %-15s\n",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
			}
			fclose(fnvm);
			remove("Nhanvien.txt");
			rename("updnv.txt","Nhanvien.txt");

			DSCong dscc[30];
			Docfilecong(dscc,&songay);
			if (songay>0){  //Neu da co cong truoc do thi xoa du lieu cong cua nhan vien bi xoa
				FILE *fc = fopen("Suacong.txt","a+");
				for (i =0; i<songay; i++){
					fprintf(fc,"%02d/%02d/%4d\n", dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
					strcpy(dscc[i].nv[slnv].Manv, nvm.MaNV);
					for (j=0; j < slnv; j++)
					{
						if (j==inv) continue;
						fprintf(fc,"%-15s %-10s %-10s\n", dscc[i].nv[j].Manv, dscc[i].nv[j].Sang, dscc[i].nv[j].Chieu );fflush(stdin);
					}
				}
				fclose(fc);
				remove("Chamcong.txt");
				rename("Suacong.txt","Chamcong.txt");
			}
			DSLuong dsluong[12];
			Docfileluong(dsluong,&sothang);
			if (sothang>0){
				FILE *fluong = fopen("Sualuong.txt","w");
				for (i=0; i<sothang; i++){
					fprintf(fluong,"%02d/%4d\n",dsluong[i].thang, dsluong[i].nam);
					strcpy(dsluong[i].nv[slnv].Manv, nvm.MaNV);
					for (j=0; j<slnv; j++){
						if (j==inv) continue; 
						fprintf(fluong,"%-10s %-15d\n",dsluong[i].nv[j].Manv, dsluong[i].nv[j].Tien);
					}
				}
				fclose(fluong);
				remove("Bangluong.txt");
				rename("Sualuong.txt","Bangluong.txt");
			}
			printf("\n\t\t\tThanh cong");
			l:
			printf("\nChon 1 de quay ve menu,chon 2 de thoat :");
			scanf("%d",&s);
			if (s==1) menu();
			else if (s==2) exit(0);
			else{
				printf("\nKhong hop le !");
				goto l;
			}
		}
		else ThongTin();
	}
	else {
		printf("\n\t\t\tKhong co trong danh sach");
		printf("\n1.Tiep tuc xoa \t 2.Tro ve \t 0.Thoat \nNhap lua chon :");
		
		while(1){
			scanf("%d",&s);
			if (s==1 || s==2 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai\nNhap lua chon : ");
		}
		if (s==1) DeleteNV();
		else if (s==2) ThongTin();
		else close();
	}
	return;
}
//Hien thi toan bo nhan vien
void ShowNV(){
	NhanVien dsnv[MAX];
	int s, i;
	Docfilenv(dsnv,&slnv);
	system("cls");
	gotoxy(x+40,5);printf("-------Danh sach nhan vien-----\n");
	box(slnv,107,x,y);
    gotoxy(x+1, y+1);printf("%-15s|%-25s|%-15s|%-15s|%-15s|%-15s","MaNV","Ho ten","Ngay sinh","Gioi tinh","Que quan","Ma CV");
	for (i=0;i<slnv;i++){
		gotoxy(x+1,y+3+i);printf("%-15s|%-25s|%02d/%02d/%4d     |%-15s|%-15s|%-15s",dsnv[i].MaNV,dsnv[i].HoTen,dsnv[i].NgaySinh.ngay, dsnv[i].NgaySinh.thang, dsnv[i].NgaySinh.nam,dsnv[i].GioiTinh,dsnv[i].QueQuan,dsnv[i].MaCV);
	}
	
	while(1){
		gotoxy(x,y+slnv+5);printf("1.Tro ve    0.Thoat :   ");
		gotoxy(x+22,y+slnv+5);scanf("%d",&s);
		if (s==1 || s==0) break;
		else printf("\a\t\t\tVui long chon 1 hoac 0");
	}
	
	if (s==1) ThongTin();
	else close();
	return;
}

//=======Menu thong tin nhan vien===================
void ThongTin(){
	system("cls");
	int a;
	box(7,40,x,y);
	gotoxy(1+x,1+y);printf("-----------Quan ly thong tin----------");
	gotoxy(1+x,3+y);printf("1.Them nhan vien");
	gotoxy(1+x,4+y);printf("2.Cap nhat thong tin nhan vien");
	gotoxy(1+x,5+y);printf("3.Tim kiem nhan vien");
	gotoxy(1+x,6+y);printf("4.Xoa nhan vien");
	gotoxy(1+x,7+y);printf("5.Hien thi toan bo nhan vien");
	gotoxy(1+x,8+y);printf("--------------------------------------");
	gotoxy(30+x,9+y);printf("0.Tro ve");
	chon:
	gotoxy(1+x,13+y);printf("Chon chuc nang :   ");
	gotoxy(17+x,13+y);scanf("%d",&a);
	if (a==0) menu();
	else if (a==1) AddNV();
	else if (a==2) UpdNV();
	else if (a==3) SearchNV();
	else if (a==4) DeleteNV();
	else if (a==5) ShowNV();
	else {
		gotoxy(1+x,15+y);printf("\aKhong hop le, vui long nhap lai");
		goto chon;
	}
	return;
}
//=======================================================
//===================Chuc vu=============================
void ChucVu();

//Doc file du lieu chuc vu
void Docfilecv(CV *ds,int *slcv){
	FILE *fcv =fopen("Chucvu.txt","r");
	int i =0;
	if(fcv){
		for (;;){
			CV cv;
			fscanf(fcv,"%10s %20[^\n] %15d %15f %15d\n",cv.MaCV, cv.TenCV, &cv.SL, &cv.HSLuong, &cv.Thuong);
			ds[i++]=cv;
			if(feof(fcv)) break;
		}
	}
	else printf("chua co du lieu chuc vu\n");
	fclose(fcv);
	*slcv=i;
}

//Them chuc vu moi
void AddCV(){
	system("cls");
	CV dscv[20];
	Docfilecv(dscv,&slcv);
	CV cvm;
	int s,i;
	nhap_ma:
    box(5,40,x,y);
	gotoxy(1+x,1+y);printf("-------------Them chuc vu-------------");

	while(1){
		gotoxy(1+x,3+y);printf("Nhap ma chuc vu :     ");fflush(stdin);
		gotoxy(18+x,3+y);gets(cvm.MaCV);
		if (strlen(cvm.MaCV) == 5) {
			int timthay=0;
			for (i=0; i<slcv; i++){
	 			char *t =strstr(dscv[i].MaCV,cvm.MaCV);
				if (t){
					timthay=1;
					break;
				}
			}
			if (timthay == 0) break;
			else {
				gotoxy(x+41,y);printf("\aMa chuc vu da ton tai !");
				goto nhap_ma;
			}
		}
		else {
			gotoxy(x+41,1+y);printf("\aSai dinh dang,ma nhan vien gom 5 ky tu !");
		}
	}
	
	gotoxy(1+x,4+y);printf("Nhap ten chuc vu : ");
	gets(cvm.TenCV);
	gotoxy(1+x,5+y);printf("Nhap so luong toi da : ");
	scanf("%d",&cvm.SL);
	gotoxy(1+x,6+y);printf("Nhap he so luong  : ");
	scanf("%f",&cvm.HSLuong);
	gotoxy(1+x,7+y);printf("Nhap tien thuong : ");
	scanf("%d",&cvm.Thuong);
	box(1,86,x,y+20);
	gotoxy(x+1,y+1+20);printf("%-15s %-20s %-15s %-15s %-15s","Ma Cv","Ten","So luong","He so luong","Thuong");
	gotoxy(x+1,y+3+20);printf("%-15s %-20s %-15d %-15.2f %-15d",cvm.MaCV, cvm.TenCV, cvm.SL, cvm.HSLuong, cvm.Thuong);
	nhaplai:
	gotoxy(x+1,y+26);printf("Xac nhan them  1.Co  2.Khong	:  ");
	scanf("%d",&s);
	if (s==2){
		menu();
	}
	else if (s==1){
		FILE *fcv=fopen("Chucvu.txt","a+");
		fprintf(fcv,"%-10s %-20s %-15d %-15.2f %-15d\n",cvm.MaCV, cvm.TenCV, cvm.SL, cvm.HSLuong, cvm.Thuong);
		fclose(fcv);
		gotoxy(x+1, y+27);printf("Da luu !");
		l:
		gotoxy(x+1, y+29);printf("Chon 1 de quay ve menu,chon 2 de thoat :  ");
		scanf("%d",&s);
		if (s==1) menu();
		else if (s==2) close();
		else{
			gotoxy(x+1,y+30);printf("\aKhong hop le !");
			goto l;
		}
	}
	else{
		gotoxy(x+1,y+30);printf("\aKhong hop le !");
		goto nhaplai;
	}
	return;
}

//Cap nhat thong tin chuc vu
void UpdCV(){
	system("cls");
	CV cvm, dscv[20];
	Docfilecv(dscv,&slcv);
	if (slcv==0){
		gotoxy(x,10);printf("\aChua co chuc vu nao !");
		gotoxy(x,11);printf("Nhan phim bat ki de quay ve");
		getch();
		menu();
		return;
	}
	int s, i;
	box(6,40,x,y);
	gotoxy(1+x,1+y);printf("------------Cap nhat chuc vu----------");
	
	while(1){
		gotoxy(1+x,3+y);printf("Nhap ma chuc vu :      ");fflush(stdin);
		gotoxy(1+x+18,3+y);gets(cvm.MaCV);
		if (strlen(cvm.MaCV) == 5) {
			int timthay=0;
			for (i=0; i<slcv; i++){
	 			char *tcv =strstr(dscv[i].MaCV,cvm.MaCV);
				if (tcv){
					timthay=1;
					break;
				}
			}
			if (timthay == 0){
				gotoxy(42+x,3+y);printf("\aMa chuc vu khong ton tai !          ");
			}
			else break;
		}
		else {
			gotoxy(42+x,3+y);printf("\aSai dinh dang,ma chuc vu gom 5 ky tu !");
		}
	}
// luc nay i = index ma chuc vu tim thay trong danh sach	
	gotoxy(1+x,4+y);printf("1.Ten chuc vu : %s",dscv[i].TenCV);
	gotoxy(1+x,5+y);printf("2.So luong toi da : %d",dscv[i].SL);
	gotoxy(1+x,6+y);printf("3.He so luong : %.2f",dscv[i].HSLuong);
	gotoxy(1+x,7+y);printf("4.Muc thuong : %d",dscv[i].Thuong);
	gotoxy(1+x,8+y);printf("5.Cap nhat tat ca");
	chon:
	gotoxy(1+x,11+y);printf("Chon thong tin can cap nhat :  ");
	gotoxy(x+30,y+11);scanf("%d",&s);
	if (s==1){
		getchar();
		box(1,25,x,y+13);
		gotoxy(x+1,y+13+1);printf("Nhap ten chuc vu moi : ");
		gotoxy(x+1,y+13+3);gets(cvm.TenCV);
		strcpy(dscv[i].TenCV, cvm.TenCV);
	}
	else if (s==2){
		box(1,25,x,y+13);
		gotoxy(x+1,y+13+1);printf("Nhap so luong :");
		gotoxy(x+1,y+13+3);scanf("%d",&cvm.SL);
		dscv[i].SL = cvm.SL;
	}
	else if (s==3){
		box(1,25,x,y+13);
		gotoxy(x+1,y+13+1);printf("Nhap he so luong : ");
		gotoxy(x+1,y+13+3);scanf("%f",&cvm.HSLuong);
		dscv[i].HSLuong = cvm.HSLuong;
	}
	else if(s==4){
		box(1,25,x,y+13);
		gotoxy(x+1,y+13+1);printf("Nhap muc thuong : ");
		gotoxy(x+1,y+13+3);scanf("%d",&cvm.Thuong);
		dscv[i].Thuong = cvm.Thuong;
	}
	else if(s==5){
		getchar();
		box(4,40,x,y+13);
		gotoxy(x+1,y+3+13);printf("Nhap ten chuc vu moi : ");
		gets(cvm.TenCV);
		strcpy(dscv[i].TenCV, cvm.TenCV);
		gotoxy(x+1,y+4+13);printf("Nhap so luong : ");
		scanf("%d",&cvm.SL);
		dscv[i].SL = cvm.SL;
		gotoxy(x+1,y+5+13);printf("Nhap he so luong : ");
		scanf("%f",&cvm.HSLuong);
		dscv[i].HSLuong = cvm.HSLuong;
		gotoxy(x+1,y+6+13);printf("Nhap muc thuong : ");
		scanf("%d",&cvm.Thuong);
		dscv[i].Thuong = cvm.Thuong;
	}
	else{
		gotoxy(x+25,y+11);printf("\aNhap sai !");
		goto chon;
	}
	
	box(1,86,x,y+21);
	gotoxy(x+1,y+1+21);printf("%-15s %-20s %-15s %-15s %-15s","Ma Cv","Ten","So luong","He so luong","Thuong");
	gotoxy(x+1,y+3+21);printf("%-15s %-20s %-15d %-15.2f %-15d",dscv[i].MaCV, dscv[i].TenCV, dscv[i].SL, dscv[i].HSLuong, dscv[i].Thuong);
	xacnhan:
	gotoxy(x+1,y+3+21+3);printf("Xac nhan luu  1.Co  2.Khong	: ");
	scanf("%d",&s);
	if (s==2){
		menu();
	}
	else if (s==1){
		getchar();
		FILE *fcvm=fopen("updcv.txt","w");
		for(i=0;i<slcv;i++){
			fprintf(fcvm,"%-10s %-20s %-15d %-15.2f %-15d\n",dscv[i].MaCV, dscv[i].TenCV, dscv[i].SL, dscv[i].HSLuong, dscv[i].Thuong);
		}
		fclose(fcvm);
		remove("Chucvu.txt");
		rename("updcv.txt","Chucvu.txt");
		gotoxy(x+40,y+28);printf("Thanh cong !");
		l:
		gotoxy(x+1,y+29);printf("Chon 1 de quay ve menu,chon 2 de thoat : ");
		scanf("%d",&s);
		if (s==1) menu();
		else if (s==2) close();
		else{
			printf("\t\t\aKhong hop le !");
			goto l;
		}
	}
	else{
		printf("\t\t\aKhong hop le !");
		goto xacnhan;
	}
}
//Xoa chuc vu
void DeleteCV(){
	system("cls");
	CV cvm, dscv[20];
	Docfilecv(dscv,&slcv);
	if (slcv==0){
		gotoxy(x,10);printf("\aChua co chuc vu nao !");
		gotoxy(x,11);printf("Nhan phim bat ki de quay ve");
		getch();
		menu();
		return;
	}
	int s, i, icv, timthay=0;
	box(1,18,x,y-5);
	while(1){
		gotoxy(x+1,y-4);printf("Nhap ma chuc vu ");fflush(stdin);
		gotoxy(x+1,y-2);
		gets(cvm.MaCV);
		if (strlen(cvm.MaCV) == 5) {
			for (i=0; i<slcv; i++){
	 			char *t =strstr(dscv[i].MaCV,cvm.MaCV);
				if (t){
					timthay=1;
					break;
				}
			}
			break;
		}
		else printf("\t\t\t\aSai dinh dang,ma chuc vu gom 5 ky tu !");
	}
	icv=i;
	if (timthay==1){
		box(1,86,x,y+2);
		gotoxy(x+1,y+1+2);printf("%-15s %-20s %-15s %-15s %-15s","Ma Cv","Ten","So luong","He so luong","Thuong");
		gotoxy(x+1,y+3+2);printf("%-15s %-20s %-15d %-15.2f %-15d",dscv[i].MaCV, dscv[i].TenCV, dscv[i].SL, dscv[i].HSLuong, dscv[i].Thuong);
		gotoxy(x+1,y+7);printf("Xac nhan xoa ? ");
		while(1){
			gotoxy(x+1,y+8);printf("1.Dong y 0.Khong  :  ");	
			gotoxy(x+21,y+8);
			scanf("%d",&s);
			if (s==1 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai !");
		}
		if (s==1) {
			if(slcv==1){
				remove("Chucvu.txt");
			}
			else{
				FILE *fnvm=fopen("updcv.txt","w");
				for(i=0;i<slcv;i++){
				if (i==icv) continue;
				fprintf(fnvm,"%-10s %-20s %-15d %-15.2f %-15d\n",dscv[i].MaCV, dscv[i].TenCV, dscv[i].SL, dscv[i].HSLuong, dscv[i].Thuong);
				}
				fclose(fnvm);
				remove("Chucvu.txt");
				rename("updcv.txt","Chucvu.txt");
			}
			slcv-=1;
			gotoxy(x,y+10);printf("Thanh cong");
		}
	}
	else {
		printf("\n\t\t\tKhong co trong danh sach");
		printf("\n1.Tiep tuc xoa \t 2.Tro ve \t 0.Thoat \nNhap lua chon :");
		
		while(1){
			scanf("%d",&s);
			if (s==1 || s==2 || s==0) break;
			else printf("\nNhap sai,vui long nhap lai\nNhap lua chon : ");
		}
		if (s==1){ DeleteCV(); return;}
		else if (s==2){ ChucVu(); return;}
		else { close(); return;}
	}
	printf("\n\t\t\t\tNhan phim bat ki de quay ve"); getch();
	ChucVu();
	return;
}

//Hien thi danh sach chuc vu
void ShowCV(){
	system("cls");
	CV cvm, dscv[20];
	Docfilecv(dscv,&slcv);
	if (slcv==0){
		gotoxy(x,10);printf("\aChua co chuc vu nao !");
		gotoxy(x,11);printf("Nhan phim bat ki de quay ve");
		getch();
		menu();
		return;
	}
	int s, i;
	gotoxy(25+x,3);printf("-------Danh sach chuc vu-----");
	box(slcv,86,x,y+7);
	gotoxy(x+1,y+1+7);printf("%-15s %-20s %-15s %-15s %-15s","Ma Cv","Ten","So luong","He so luong","Thuong");
	for (i=0;i<slcv;i++){
			gotoxy(x+1,y+3+7+i);printf("%-15s %-20s %-15d %-15.2f %-15d",dscv[i].MaCV, dscv[i].TenCV, dscv[i].SL, dscv[i].HSLuong, dscv[i].Thuong);
	}
	while(1){
		gotoxy(x,y+slcv+5+7);printf("1.Tro ve\t 0.Thoat  : ");
		scanf("%d",&s);
		if (s==1 || s==0) break;
		else printf("\n\t\t\t\aVui long chon 1 hoac 0\n");
	}
	if (s==1) ChucVu();
	else close();
}


//menu chuc vu
void ChucVu(){
	system("cls");
	int a;
	box(6,40,x,y);
	gotoxy(1+x,1+y);printf("------------Quan ly chuc vu-----------");
	gotoxy(1+x,3+y);printf("1.Them 1 chuc vu");
	gotoxy(1+x,4+y);printf("2.Cap nhat thong tin chuc vu");
	gotoxy(1+x,5+y);printf("3.Xoa chuc vu");
	gotoxy(1+x,6+y);printf("4.Hien thi danh sach chuc vu");
	gotoxy(1+x,7+y);printf("--------------------------------------");
	gotoxy(30+x,8+y);printf("0.Tro ve");
	chon:
	gotoxy(1+x,13+y);printf("Chon chuc nang :   ");
	gotoxy(17+x,13+y);scanf("%d",&a);
	switch(a){
		case 0: menu();break;
		case 1: AddCV();break;
		case 2: UpdCV();break;
		case 3: DeleteCV();break;
		case 4: ShowCV();break;
		default: 
		gotoxy(x+1,y+15);printf("\aNhap sai,vui long nhap lai !");
		goto chon;
		break;
	}
}

//===============================================================
//==========================Cham cong=============================
void ChamCong();

//Doc du lieu cham cong
void Docfilecong(DSCong *ds,int *songay){
	FILE *fc=fopen("Chamcong.txt","r");
	int i=0,j;
	if (fc){
		for(;;){
			DSCong cong;
			fscanf(fc,"%02d/%02d/%4d\n",&cong.Ngay.ngay, &cong.Ngay.thang, &cong.Ngay.nam);
			for (j=0;j<slnv;j++){
				fscanf(fc,"%15s %10s %10s\n",cong.nv[j].Manv, cong.nv[j].Sang, cong.nv[j].Chieu);
			}
			ds[i++]=cong;
			if(feof(fc)) break;
		}
	}
	else {
		gotoxy(160,0);printf("Chua ton tai du lieu cong");
	}
	fclose(fc);
	*songay=i;
}


void Cham(){//Cham cong
	system("cls");
	NhanVien dsnv[MAX];
	DSCong dscc[30], cc;
	int i, j;
	int s;  //lua chon
	Docfilenv(dsnv, &slnv);
	Docfilecong(dscc,&songay);
	if (songay>0){
		box(songay,23,x+81,0);
		gotoxy(x+82,1);printf("Ngay da cham cong :");
		for (i=0; i<songay; i++){
			gotoxy(x+83,3+i);printf("%02d/%02d/%4d",dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
		}
	}
	box(1,20,0,0);
	nhapngay:
	gotoxy(2,1);printf("Nhap ngay cham : ");
    gotoxy(3,3);printf("          ");
	gotoxy(3,3);scanf("%02d/%02d/%4d",&cc.Ngay.ngay, &cc.Ngay.thang, &cc.Ngay.nam);
	switch (cc.Ngay.thang)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 31){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		} 
		break;
	case 2:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 29){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	default:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 30){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	}
	if (cc.Ngay.thang < 1 || cc.Ngay.thang > 12){
		printf("\n\aNhap sai ngay \n");
		goto nhapngay;
	}

	for (i = 0; i<slnv; i++){
		if (dscc[i].Ngay.ngay == cc.Ngay.ngay && dscc[i].Ngay.thang == cc.Ngay.thang && dscc[i].Ngay.nam == cc.Ngay.nam) {
			printf("\aDa cham cong ngay nay !");
			while(1){
			printf("1.Tro ve\t 0.Thoat  : ");
			scanf("%d",&s);
			if (s==1 || s==0) break;
			else {printf("\n\t\t\tVui long chon 1 hoac 0\n");}
			}
			if (s==1) {ChamCong();return;}
			else {close(); return;}
		}
	}
	box(slnv,80,x,y);
    gotoxy(1+x,1+y); printf("%-20s|%-25s|%-15s|%-15s","Ma nhan vien", "Ho ten", "Sang", "Chieu");
	for (i=0; i<slnv; i++){
        gotoxy(1+x,3+i+y);
        printf("%-20s|%-25s|%-15s|%-15s", dsnv[i].MaNV, dsnv[i].HoTen, "", "");
    }
	
	for (j=0; j<slnv; j++){
        fflush(stdin);
		strcpy(cc.nv[j].Manv , dsnv[j].MaNV);
        while (1){
			gotoxy(48+x,3+j+y);printf("   ");
            gotoxy(48+x,3+j+y);scanf("%s",cc.nv[j].Sang);
            if (strcmp(cc.nv[j].Sang,"x")==0 || strcmp(cc.nv[j].Sang,"o")==0) break;
            else {
                gotoxy(x+1,y+slnv+4);printf("\aNhap sai,vui long nhap lai !");
            }
        }
        fflush(stdin);
        while (1){
			gotoxy(64+x,3+j+y);printf("   ");
            gotoxy(64+x,3+j+y);scanf("%s",cc.nv[j].Chieu);
            if (strcmp(cc.nv[j].Chieu,"x")==0 || strcmp(cc.nv[j].Chieu,"o")==0) break;
            else {
                gotoxy(x+1,y+slnv+4);printf("\aNhap sai,vui long nhap lai !");
            }
        } 
		 
    }
	while(1){
		gotoxy(x+1,slnv+y+4);printf("Xac nhan luu ? (1.Co  0.Khong) :  ");
		gotoxy(x+33,slnv+y+4);scanf("%d",&s);
		if (s==1 || s==0) break;
		else {gotoxy(x,slnv+y+5);printf("\a\t\t\tVui long chon 1 hoac 0");}
	}
	if (s==1){
		FILE *fn = fopen("Chamcong.txt","a+");
		fprintf(fn,"%02d/%02d/%4d\n", cc.Ngay.ngay, cc.Ngay.thang, cc.Ngay.nam);
		for (j=0; j<slnv; j++){
			fprintf(fn,"%-15s %-10s %-10s\n", cc.nv[j].Manv, cc.nv[j].Sang, cc.nv[j].Chieu);fflush(stdin);
		}
		fclose(fn);
	}
	else {
		ChamCong();
		return;
	}
	gotoxy(x+20,slnv+y+6);printf("Da luu !");
	gotoxy(x+20,slnv+y+7);printf("Nhan phim bat ki de quay ve");
	getch();
	ChamCong();
 	return;
}

//Sua doi cong
void SuaCong(){
	system("cls");
	NhanVien dsnv[MAX];
	DSCong dscc[30], cc;
	int i, j;
	int dacham =0;
	int ingay, inv;
	int s;  //lua chon
	char mnv[6];//ma nhan vien nhap vao
	char congsang[2],congchieu[2];
	Docfilenv(dsnv, &slnv);
	Docfilecong(dscc,&songay);
	if (songay>0){
		box(songay,23,x+81,y);
		gotoxy(x+82,y+1);printf("Ngay da cham cong :");
		for (i=0; i<songay; i++){
			gotoxy(x+83,y+3+i);printf("%02d/%02d/%4d",dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
		}
	}
	box(1,20,0,0);
	nhapngay:
	gotoxy(1,1);printf("Nhap ngay muon sua : ");
    gotoxy(1,3);printf("          ");
	gotoxy(3,3);scanf("%02d/%02d/%4d",&cc.Ngay.ngay, &cc.Ngay.thang, &cc.Ngay.nam);
	switch (cc.Ngay.thang)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 31){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		} 
		break;
	case 2:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 29){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	default:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 30){
			printf("\n\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	}
	if (cc.Ngay.thang < 1 || cc.Ngay.thang > 12){
		printf("\n\aNhap sai ngay \n");
		goto nhapngay;
	}

	for (i = 0; i<slnv; i++){
		if (dscc[i].Ngay.ngay == cc.Ngay.ngay && dscc[i].Ngay.thang == cc.Ngay.thang && dscc[i].Ngay.nam == cc.Ngay.nam) { dacham = 1; ingay =i; }
	}

	if (dacham==0){
		printf("\aChua cham cong ngay nay !");
		while(1){
			printf("\n1.Tro ve\t 0.Thoat  : ");
			scanf("%d",&s);
			if (s==1 || s==0) break;
			else {printf("\n\t\t\t\aVui long chon 1 hoac 0\n");}
		}
		if (s==1) {ChamCong();return;}
		else close();
	}
	else{
		box(slnv,80,x,y);
    	gotoxy(1+x,1+y); printf("%-20s|%-25s|%-15s|%-15s","Ma nhan vien", "Ho ten", "Sang", "Chieu");
		for (i=0; i<slnv; i++){
    	    gotoxy(1+x,3+i+y);
    	    printf("%-20s|%-25s|%-15s|%-15s", dsnv[i].MaNV, dsnv[i].HoTen, dscc[ingay].nv[i].Sang, dscc[ingay].nv[i].Chieu );
    	}
		gotoxy(1+x,slnv + y+5);printf("Nhap ma nhan vien : ");
		nhapmnv://nhap ma nhan vien
		gotoxy(29+x,slnv + y+5);scanf("%s",mnv);
		while(1){
			if (strlen(mnv) == 5) {
				int timthay=0;
				for (i=0; i<slnv; i++){
					char *t =strstr(dsnv[i].MaNV,mnv);
					if (t){
						timthay=1;
						inv=i;
						break;
					}
				}
				if (timthay == 0){
					gotoxy(1+x,slnv+y+7);printf("Ma nhan vien khong ton tai");
					goto nhapmnv;
				}
				else break;
			}
			else {
				gotoxy(1+x,slnv+y+7);printf("Sai dinh dang,ma nhan vien gom 5 ky tu !");
				goto nhapmnv;
			}

		}
		//tiep//
		gotoxy(1+x,slnv+y+7);printf("%-20s|%-25s|%-15s|%-15s","Ma nhan vien", "Ho ten", "Sang", "Chieu");
		gotoxy(1+x,slnv+y+8);printf("%-20s|%-25s|%-15s|%-15s",dsnv[inv].MaNV, dsnv[inv].HoTen, "   ", "   ");
		
		while (1){
			fflush(stdin);
            gotoxy(48+x,slnv+y+8);scanf("%s",congsang);
            if (strcmp(congsang,"x")==0 || strcmp(congsang,"o")==0) break;
            else {
                gotoxy(1+x,slnv+y+10);printf("\aNhap sai,vui long nhap lai !");
            }
        }
		while (1){
			fflush(stdin);
            gotoxy(64+x,slnv+y+8);scanf("%s",congchieu);
            if (strcmp(congchieu,"x")==0 || strcmp(congchieu,"o")==0) break;
            else {
                gotoxy(1+x,slnv+y+10);printf("\aNhap sai,vui long nhap lai !");
            }
        }
		strcpy(dscc[ingay].nv[inv].Sang, congsang);
		strcpy(dscc[ingay].nv[inv].Chieu, congchieu);

		FILE *fc = fopen("Suacong.txt","a+");
		for ( i = 0; i < songay; i++)
		{
			fprintf(fc,"%02d/%02d/%4d\n", dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
			for (j=0; j < slnv; j++)
			{
				fprintf(fc,"%-15s %-10s %-10s\n", dscc[i].nv[j].Manv, dscc[i].nv[j].Sang, dscc[i].nv[j].Chieu);fflush(stdin);
			}
		}
		fclose(fc);
		remove("Chamcong.txt");
		rename("Suacong.txt","Chamcong.txt");
		gotoxy(1+x,slnv+y+12);printf("Thay doi thanh cong !");
		getch();
		ChamCong();
	}
	return;
}

//Hien thi bang cong
void BangCong(){
	system("cls");
	NhanVien dsnv[MAX];
	DSCong dscc[30], cc;
	int i, j;
	int s;  //lua chon
	int dacham =0;
	int ingay, inv;
	Docfilenv(dsnv, &slnv);
	Docfilecong(dscc,&songay);
	if (songay>0){
		box(songay,23,x+81,0);
		gotoxy(x+82,0+1);printf("Ngay da cham cong ");
		for (i=0; i<songay; i++){
			gotoxy(x+83,0+3+i);printf("%02d/%02d/%4d",dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
		}
	}
	box(1,20,0,0);
	nhapngay:
    gotoxy(3,1);printf("Ngay hien thi :");
    gotoxy(3,3);printf("          ");
	gotoxy(3,3);scanf("%02d/%02d/%4d",&cc.Ngay.ngay, &cc.Ngay.thang, &cc.Ngay.nam);
	switch (cc.Ngay.thang)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 31){
			printf("\t\t\t\t\t\t\aNhap sai ngay \n");
			goto nhapngay;
		} 
		break;
	case 2:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 29){
			printf("\t\t\t\t\t\t\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	default:
		if (cc.Ngay.ngay < 1 || cc.Ngay.ngay > 30){
			printf("\t\t\t\t\t\t\aNhap sai ngay \n");
			goto nhapngay;
		}
		break;
	}
	if (cc.Ngay.thang < 1 || cc.Ngay.thang > 12){
		printf("\t\t\t\t\t\t\aNhap sai ngay \n");
		goto nhapngay;
	}

	for (i = 0; i<slnv; i++){
		if (dscc[i].Ngay.ngay == cc.Ngay.ngay && dscc[i].Ngay.thang == cc.Ngay.thang && dscc[i].Ngay.nam == cc.Ngay.nam) { dacham = 1; ingay =i; }
	}

	if (dacham==0){
		printf("\aChua cham cong ngay nay !");
		while(1){
			printf("\n1.Tro ve\t 0.Thoat  : ");
			scanf("%d",&s);
			if (s==1 || s==0) break;
			else {printf("\n\t\t\t\aVui long chon 1 hoac 0\n");}
		}
		if (s==1) {ChamCong();return;}
		else close();
	}
	else{
		box(slnv,80,x,y);
    	gotoxy(1+x,1+y); printf("%-20s|%-25s|%-15s|%-15s","Ma nhan vien", "Ho ten", "Sang", "Chieu");
		for (i=0; i<slnv; i++){
    	    gotoxy(1+x,3+i+y);
    	    printf("%-20s|%-25s|%-15s|%-15s", dsnv[i].MaNV, dsnv[i].HoTen, dscc[ingay].nv[i].Sang, dscc[ingay].nv[i].Chieu );
    	}
		gotoxy(1+x,slnv+y+5);printf("x : Co lam			o : Khong lam			0 : Chua lam");
		gotoxy(1+x,slnv+y+12);printf("Nhap phim bat ki de quay ve");
		getch();
		ChamCong();
	}
	
	return;
}

void ChamCong(){//Menu cham cong
	int s; //lua chon
	system("cls");
	box(4,40,x,y);
	gotoxy(10+x,1+y);printf("Cham cong nhan vien");
	gotoxy(2+x,3+y);printf("1.Cham cong");
	gotoxy(2+x,4+y);printf("2.Sua cong");
	gotoxy(2+x,5+y);printf("3.Hien thi bang cong");
	gotoxy(30+x,6+y);printf("0.Tro ve");
	nhap://nhap lua chon
	gotoxy(2+x,8+y);printf("Nhap lua chon :  ");
	gotoxy(18+x,8+y);scanf("%d",&s);
	switch ((int)s)
	{
	case 0: menu();break;
	case 1: Cham();break;
	case 2: SuaCong();break;
	case 3: BangCong();break;
	default:
	gotoxy(2+x,10+y);printf("\aNhap sai,vui long nhap lai !");
	goto nhap;
	break;
	}
	return;
}


//============================================================================
void LuongNV();
//Doc du lieu luong
void Docfileluong(DSLuong *ds,int *sothang){
	FILE *fc=fopen("Bangluong.txt","r");
	int i=0,j;
	if (fc){
		for(;;){
			DSLuong l;
			fscanf(fc,"%02d/%4d\n", &l.thang, &l.nam);
			for (j=0;j<slnv;j++){
				fscanf(fc,"%10s %15d\n", l.nv[j].Manv, &l.nv[j].Tien);
			}
			ds[i++]=l;
			if(feof(fc)) break;
		}
	}
	else {
		gotoxy(160,0);printf("Chua ton tai du lieu luong");
	}
	fclose(fc);
	*sothang=i;
}

//Dem so cong trong thang cua nhan vien
int TinhCong(DSCong *ds, int thang, int nam, char manv[6]){
	int i1, j1, socong=0;
	for (i1=0;i1<songay;i1++){
		if (ds[i1].Ngay.thang == thang && ds[i1].Ngay.nam == nam){
			for(j1=0; j1<slnv; j1++){
				if (strcmp(ds[i1].nv[j1].Manv, manv)==0){
					if (strcmp(ds[i1].nv[j1].Sang,"x")==0 ) socong+=1;
					if (strcmp(ds[i1].nv[j1].Chieu,"x")==0 ) socong+=1;
				}
				
			}	
		}
	}
	return socong;
}

//Tinh tien tuong ung voi so cong
int TinhTien(int c, char manv[6]){
	int i2,j2,tien;
	NhanVien dsnv[MAX];
	CV dscv[10];
	Docfilenv(dsnv,&slnv);
	Docfilecv(dscv,&slcv);
	for (i2=0; i2<slnv; i2++){
		if (strcmp(dsnv[i2].MaNV,manv)==0){
			for(j2=0; j2<slcv; j2++){
				if (strcmp(dscv[j2].MaCV,dsnv[i2].MaCV)==0){
					tien = c*luong1c+dscv[j2].Thuong;
					return tien;
				}
			}
		}
	}
	return 0;
}

//Tinh luong
void TinhLuong(){
	system("cls");
	int i, j;
	int month,year;
	NhanVien dsnv[MAX];
	CV dscv[20];
	DSCong dscc[30], cc;
	DSLuong dsluong[13],dsl;
	Docfilenv(dsnv,&slnv);
	Docfilecv(dscv,&slcv);
	Docfilecong(dscc,&songay);
	Docfileluong(dsluong,&sothang);
	if (sothang>0){
		box(sothang,23,x+61,y);
		gotoxy(x+62,y+1);printf("Thang da tinh luong :");
		for (i=0; i<sothang; i++){
			gotoxy(x+62,y+3+i);printf("%d/%d",dsluong[i].thang, dsluong[i].nam);
		}
	}
	if (songay>0){
		box(songay,23,x+81+5,y);
		gotoxy(x+82+5,y+1);printf("Ngay da cham cong :");
		for (i=0; i<songay; i++){
			gotoxy(x+83+5,y+3+i);printf("%02d/%02d/%4d",dscc[i].Ngay.ngay, dscc[i].Ngay.thang, dscc[i].Ngay.nam);
		}
	}
	int s;  //lua chon
	box(2,30,0,0);
	gotoxy(1,1);printf("Nhap thang");
	while(1){
		gotoxy(1,3);printf("Thang :      ");
		gotoxy(8,3);scanf("%d",&month);
		if (month>=1 && month<=12) break;
		else{
			gotoxy(1,13);printf("\aKhong hop le !");
		}
	}
	while(1){
		gotoxy(1,4);printf("Nam :      ");
		gotoxy(6,4);scanf("%d",&year);
		if (year>=1900 && year<=3000) break;
		else{
			gotoxy(1,13);printf("\aKhong hop le !");
		}
	}
	int timthay=0;
	for (i=0; i<songay; i++){
		if (month == dscc[i].Ngay.thang && year == dscc[i].Ngay.nam ){
			timthay=1;break;
		}
	}
	if (timthay==0) {
		gotoxy(0,14);printf("Chua co cong thang nay !");
		gotoxy(0,16);printf("Nhan phim bat ki de quay ve");
		getch();
		LuongNV();
		return;
	}
	timthay=0;
	for (i=0; i<sothang; i++){
		if (dsluong[i].thang == month && dsluong[i].thang == year){
			timthay=1;break;
		}
	}
	if (timthay==1){
		gotoxy(0,14);printf("Da tinh luong thang nay !");
		gotoxy(0,16);printf("Nhan phim bat ki de quay ve");
		getch();
		LuongNV();
		return;
	}

	dsl.thang = month;
	dsl.nam = year;
	box(slnv,59,x,y);
	gotoxy(x+15,y+1);printf("     Bang luong");
	for (i=0;i<slnv; i++){
		strcpy(dsl.nv[i].Manv,dsnv[i].MaNV);
		int cong = TinhCong(dscc, month, year, dsl.nv[i].Manv);
		dsl.nv[i].Tien = TinhTien(cong, dsnv[i].MaNV);
		gotoxy(1+x,3+y+i);printf("%-15s|%-25s|%-15d",dsl.nv[i].Manv, dsnv[i].HoTen, dsl.nv[i].Tien);
	}

	gotoxy(1+x,slnv+5+y);printf("Xac nhan luu bang luong ? 1.Co    0.Khong");
	while(1){
		gotoxy(1+x,slnv+y+6);scanf("%d",&s);
		if (s==1 || s==0) break;
		else {
			gotoxy(1+x,slnv+y+8);printf("\aKhong hop le");
		}
	}
	if (s==1){
		FILE *fluong = fopen("Bangluong.txt","a+");
		fprintf(fluong, "%02d/%4d\n", dsl.thang, dsl.nam);
		for (i=0; i<slnv; i++){
			fprintf(fluong, "%-10s %-15d\n", dsl.nv[i].Manv, dsl.nv[i].Tien);
		}
		fclose(fluong);
		gotoxy(8.+x,slnv+y+10);printf("Thanh cong !");
		gotoxy(1+x,slnv+y+12);printf("Nhan phim bat ki de quay ve");
		getch();
		LuongNV();
	}
	else LuongNV();
	return;
}
//Hien bang luong
void BangLuong (){
	system("cls");
	int i;
	int ithang;
	int month,year;
	NhanVien dsnv[MAX];
	DSLuong dsluong [13];
	Docfilenv(dsnv,&slnv);
	Docfileluong(dsluong,&sothang);
	if (sothang>0){
		box(sothang,23,x+61,y);
		gotoxy(x+62,y+1);printf("Thang da tinh luong :");
		for (i=0; i<sothang; i++){
			gotoxy(x+62,y+3+i);printf("%d/%d",dsluong[i].thang, dsluong[i].nam);
		}
	}

	box(2,30,0,0);
	gotoxy(1,1);printf("          Nhap thang");
	while(1){
		gotoxy(1,3);printf("Thang :      ");
		gotoxy(8,3);scanf("%d",&month);
		if (month>=1 && month<=12) break;
		else{
			gotoxy(1,13);printf("\aKhong hop le !");
		}
	}
	while(1){
		gotoxy(1,4);printf("Nam :      ");
		gotoxy(6,4);scanf("%d",&year);
		if (year>=1900 && year<=3000) break;
		else{
			gotoxy(1,13);printf("\aKhong hop le !");
		}
	}
	int timthay=0;
	for (i=0; i<sothang; i++){
		if (month == dsluong[i].thang && year == dsluong[i].nam ){
			timthay=1;
			ithang = i;
			break;
		}
	}
	if (timthay==0) {
		gotoxy(0,14);printf("Chua co luong thang nay !");
		gotoxy(0,16);printf("Nhap phim bat ki de quay ve");
		getch();
		LuongNV();
	}
	box(slnv,59,x,y);
	gotoxy(x+15,y+1);printf("Bang luong thang %d nam %d",month,year);
	for (i=0;i<slnv; i++){
		gotoxy(1+x,3+y+i);printf("%-15s|%-25s|%-15d",dsluong[ithang].nv[i].Manv, dsnv[i].HoTen, dsluong[ithang].nv[i].Tien);
	}
	gotoxy(1+x,slnv+y+12);printf("Nhan phim bat ki de quay ve");
	getch();
	LuongNV();
	return;
}
//===
//menu tinh luong
void LuongNV(){
	system("cls");
	int a;
	box(5,40,x,y);
	gotoxy(1+x,1+y);printf("--------------Tinh luong--------------");
	gotoxy(1+x,3+y);printf("1.Tinh luong");
	gotoxy(1+x,4+y);printf("2.Xem bang luong");
	gotoxy(1+x,6+y);printf("--------------------------------------");
	gotoxy(30+x,7+y);printf("0.Thoat");
	while (1){
		gotoxy(1+x,9+y);printf("Chon chuc nang :   ");
		gotoxy(17+x,9+y);scanf("%d",&a);
		if (a==0 || a==1 || a==2 || a==3) break;
		else {
			gotoxy(1+x,11+y);printf("\aKhong hop le");
		}
	}
	
	if (a==0) menu();
	else if (a==1) TinhLuong();
	else if (a==2) BangLuong();
	return;
}

//======Thong ke

void BangThongKe(){
	system("cls");
	int i, i1, j;
	int month,year;
	NhanVien dsnv[MAX];
	DSCong dscc[30];
	DSLuong dsluong[13];
	ThongKe tk;
	Docfilenv(dsnv,&slnv);
	Docfilecong(dscc,&songay);
	Docfileluong(dsluong,&sothang);
	box(slnv,88,x,y);
	gotoxy(x+1,y+1);printf("%-10s|%-25s|%-10s|%-10s|%-11s  |%-12s","Ma NV", "Ho ten", "Ngay lam", "Ngay nghi","Ti le nghi","Luong TB");
	for (i=0; i<slnv; i++){
		float tongcong=0;	
		float tongluong=0;
		for (i1=1; i1<=12; i1++){
			tongcong = tongcong + TinhCong(dscc,i1,dscc[j].Ngay.nam,dsnv[i].MaNV);
		}
		for (j=0; j<sothang; j++){
			tongluong = tongluong + dsluong[j].nv[i].Tien;
		}
		tk.NLam = tongcong/2;
		tk.NNghi = songay - tk.NLam;
		tk.TLNghi = (tk.NNghi)/(songay) *100;
		tk.LuongTB = tongluong / sothang;
		gotoxy(1+x,y+3+i);printf("%-10s|%-25s|%-10.1f|%-10.1f|%-4.2f %%      |%-12.1f",dsnv[i].MaNV, dsnv[i].HoTen, tk.NLam, tk.NNghi, tk.TLNghi, tk.LuongTB);
	}
	gotoxy(x+10,y+slnv+10);printf("Nhap phim bat ki de quay ve");
	getch();
	menu();
	return;
}
//Quan ly database
void Dulieu(){
	int a;
    system("cls");
    box(7,40,x,y);
	gotoxy(1+x,1+y);printf("---------------Database---------------");
	gotoxy(1+x,3+y);printf("1.Xoa du lieu nhan vien");
	gotoxy(1+x,4+y);printf("2.Xoa du lieu chuc vu");
	gotoxy(1+x,5+y);printf("3.Xoa du lieu cham cong");
	gotoxy(1+x,6+y);printf("4.Xoa du lieu luong");
	gotoxy(1+x,7+y);printf("5.Xoa tat ca du lieu");
	gotoxy(1+x,8+y);printf("--------------------------------------");
	gotoxy(30+x,9+y);printf("0.Tro ve");
	chon:
	gotoxy(1+x,13+y);printf("Chon chuc nang :   ");
	gotoxy(17+x,13+y);scanf("%d",&a);
	if (a==0) menu();
	else if (a==1) {
		remove("Nhanvien.txt");
		loading();
		printf("Da xoa !");
	}
	else if (a==2) {
		remove("Chucvu.txt");
		loading();
		printf("Da xoa !");
	}
	else if (a==3) {
		remove("Chamcong.txt");
		loading();
		printf("Da xoa !");
	}
	else if (a==4) {
		remove("Bangluong.txt");
		loading();
		printf("Da xoa !");
	}
	else if (a==5) {
		remove("Nhanvien.txt");
		remove("Chucvu.txt");
		remove("Chamcong.txt");
		remove("Bangluong.txt");
		loading();
		printf("Da xoa !");
	}
	printf("\nNhap phim bat ki de quay ve");
	getch();
	menu();
	return;
}

//Menu bat dau
void menu(){
	int a;
	system("cls");
	box(8,40,x,y);
	gotoxy(1+x,1+y);printf("-----------Quan ly nhan vien----------");
	gotoxy(1+x,3+y);printf("1.Quan ly thong tin nhan vien");
	gotoxy(1+x,4+y);printf("2.Quan ly chuc vu");
	gotoxy(1+x,5+y);printf("3.Cham cong");
	gotoxy(1+x,6+y);printf("4.Luong");
	gotoxy(1+x,7+y);printf("5.Thong ke");
	gotoxy(1+x,8+y);printf("6.Quan ly co so du lieu");
	gotoxy(1+x,9+y);printf("--------------------------------------");
	gotoxy(30+x,10+y);printf("0.Thoat");
	while (1){
		gotoxy(1+x,13+y);printf("Chon chuc nang :    ");
		gotoxy(17+x,13+y);scanf("%d",&a);
		if (a==0 || a==1 || a==2 || a==3 || a==4 || a==5 || a==6) break;
		else {
			gotoxy(1+x,15+y);printf("\aKhong hop le, vui long nhap lai");
		}
		char key;
   		if(kbhit()){
   		    key = getch();
   		    if(key == 27){
   		        break;
   		    }
   		}
	}
	if (a==0) close();
	else if (a==1) ThongTin();
	else if (a==2) ChucVu();
	else if (a==3) ChamCong();
	else if (a==4) LuongNV();
	else if (a==5) BangThongKe();
	else if (a==6) Dulieu();
	return;
}

int main(){
	system("cls");
	gotoxy(x,y);
	printf("Vui long phong to man hinh de toi uu hien thi\n\n\n\n ---> Nhan phim bat ki de tiep tuc");
	getch();
	gotoxy(x,y+3);printf("Xin cam on");
	loading();
	char pass[10],password[10]="quanghuy";
    int s, i=0;
	dangnhap:
	system("cls");
	box(1,26,92,y+4);
    gotoxy(92+1,y+5);printf("Nhap mat khau dang nhap");
    gotoxy(92+7,y+7);scanf("%s",pass);
    if (strcmp(pass,password)==0) {
		gotoxy(93,y+10);printf("Dang nhap thanh cong !");
		gotoxy(99,y+15);printf("LOADING.");
        for(i=0;i<=6;i++) {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        menu();
    }
    else{   
		fflush(stdin);
		gotoxy(93,y+10);printf("Sai mat khau!!\a");
        login_try:
        gotoxy(93,y+11);printf("\nNhap 1 de dang nhap lai ,0 de thoat:");
        scanf("%d",&s);
        if (s==1) {
            system("cls");
            goto dangnhap;
        }
        else if (s==0) {
            system("cls");
            close();
		}
        else {
			gotoxy(93,y+12);printf("\nKhong hop le!");
            fordelay(100000000);
        	system("cls");
            goto login_try;
		}
    }
    return 0;
}
