// graph_alg.cpp: определяет точку входа для консольного приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <limits>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#define Inf numeric_limits<int>::max()

using namespace std;
//Алгоритм Брона-Кербоша
/*  M — текущее независимое множество;
	G[M] — множество вершин, смежных с M;
	K — множество кандидатов, т. е. вершин, каждая из которых
	может быть добавлена в M;
	P — множество просмотренных вершин, каждая из которых не
	может быть добавлена в текущее M, так как уже добавлялась
	ранее.
*/
vector<set<int>> BK(vector<vector<int>> matrix,int size){
	set <int> M,G,K,P;
	vector<set<int>> result;
	FILE *out=fopen("BK_out.txt","w");

	for (int i=0; i<size;i++)
		K.insert(i);
	int v,Count=0,cnt=0;
	int Stack1[100];
	std::set<int> Stack2[100];
	std::set<int>::iterator theIterator;
	theIterator=K.begin();
	while ((K.size()!=0)||(M.size()!=0)){
		if (K.size()!=0){
			theIterator=K.begin();
			v=*theIterator;
			Stack2[++Count]=M;
			Stack2[++Count]=K;
			Stack2[++Count]=P;
			Stack1[++cnt]=v;
			M.insert(v);
			for (int i=0;i<size;i++){
				if (matrix[v][i]){
					theIterator=K.find(i);
					if (theIterator!=K.end())
						K.erase(theIterator);
					theIterator=P.find(i);
					if (theIterator!=P.end())
						P.erase(theIterator);
				}
			}
			theIterator=K.find(v);
			if (theIterator!=K.end())
				K.erase(theIterator);
#ifdef _DEBUG			
			printf("M: ");
			for(std::set<int>::iterator it=M.begin();it!=M.end();it++)
				printf("%d ",*it);
			printf("\nK: ");
			for(std::set<int>::iterator it=K.begin();it!=K.end();it++)
				printf("%d ",*it);
			printf("\nP: ");
			for(std::set<int>::iterator it=P.begin();it!=P.end();it++)
				printf("%d ",*it);
			printf("\n");
#endif
		}else{
			if (P.size()==0){
				result.push_back(M);
				for(set<int>::iterator it=M.begin();it!=M.end();it++){
					//printf("%d ",*it+1);
					fprintf(out,"%d ",*it+1);
				}
				//printf("\n");
				fprintf(out,"\n");
			}
			v=Stack1[cnt--];
			P=Stack2[Count--];
			K=Stack2[Count--];
			M=Stack2[Count--];
#ifdef _DEBUG
			printf("M: ");
			for(std::set<int>::iterator it=M.begin();it!=M.end();it++)
				printf("%d ",*it);
			printf("\nK: ");
			
			for(std::set<int>::iterator it=K.begin();it!=K.end();it++)
				printf("%d ",*it);
			printf("\nP: ");
			for(std::set<int>::iterator it=P.begin();it!=P.end();it++)
				printf("%d ",*it);
			printf("\n");
#endif
			theIterator=K.find(v);
			if (theIterator!=K.end())
				K.erase(theIterator);
			P.insert(v);
		}
	}

	return result;
}
//-----------------------------------------------
//Алгоритм Прима
int Prim(vector<vector<int>> matrix,int size){
	//Заполняем матрицу бесконечностями, если вес <= 0
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(matrix[i][j]<=0)matrix[i][j]=Inf;
#ifdef _DEBUG
			matrix[i][j]!=Inf?printf("%d,%d: %d\t",i,j,matrix[i][j]):printf("%d,%d: %c\t",i,j,8223);
#endif
		}
#ifdef _DEBUG
		printf("\n");
#endif
	}
	// алгоритм
	int finalWeight=0;
	vector<bool> used (size);
	vector<int> min_e (size, Inf), result (size, -1);
	min_e[0] = 0;
	printf("---=---\nResult:\n");
	for (int i=0; i<size; ++i) {
		int v = -1; //Текущая вершина
		for (int j=0; j<size; ++j)
			if (!used[j] && (v==-1 || min_e[j]<min_e[v]))
				v = j;
		if (min_e[v] == Inf) {
			printf("No minimal spanning tree!");
			return 0;
		}
 
		used[v] = true;
		if (result[v] != -1){
			printf("%d\t<->\t%d\n",v+1,result[v]+1);
			finalWeight+=matrix[result[v]][v];
		}
		for (int i=0; i<size; i++)
			if (matrix[v][i] < min_e[i]) {
				min_e[i] = matrix[v][i];
				result[i] = v;
			}
	}
	return 0;
}
//-----------------------------------------------
//Алгоритм Краскала
struct edge{
    int x, y, w;
    edge(){}
    edge(int x, int y, int w): x(x), y(y), w(w) {}
};
bool operator==(const edge& lhs, const edge& rhs){
	if(lhs.x==rhs.x&&lhs.y==rhs.y||lhs.x==rhs.y&&lhs.y==rhs.x)return 1;
	else return 0;
}
bool cmp(const edge& a, const edge& b){
    return a.w < b.w;
}

vector <int> whereV;
int GetwhereVIs(int x){
    if (x == whereV[x])
        return x;

    return whereV[x] = GetwhereVIs(whereV[x]);    
}

bool unite(int x, int y){
    x = GetwhereVIs(x);
    y = GetwhereVIs(y);

    if (x == y)
        return false;

    whereV[x] = y;
    return true;
}

int Kruskal(vector<vector<int>> matrix,int size){
	vector <edge> e(1);
	//Заполняем матрицу бесконечностями, если вес <= 0
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(matrix[i][j]<=0)matrix[i][j]=Inf;

#ifdef _DEBUG
			matrix[i][j]!=Inf?printf("%d,%d: %d\t",i,j,matrix[i][j]):printf("%d,%d: %c\t",i,j,8223);
#endif
		}
#ifdef _DEBUG
		printf("\n");
#endif
	}
	int ix=0;
    for (int i=0; i<size; i++){
		for(int j=i;j<size;j++){
			if(matrix[i][j]!=Inf){
				e[ix].x=i;
				e[ix].y=j;
				e[ix].w=matrix[i][j];
#ifdef _DEBUG
				printf("%d-%d:%d\n",e[ix].x,e[ix].y,e[ix].w);
#endif
				ix++;
				e.resize(ix+1);
			}
		}
    }

    sort(e.begin(), e.end(), cmp);

	whereV.resize(e.size());
    for (int i = 0; i < e.size(); i++)
        whereV[i] = i;
	//for(int i=0;i<e.size();i++)printf("%d-%d:%d\n",e[i].x,e[i].y,e[i].w);
    vector <edge> result;
	for (int i=0; i<e.size()-1; i++){
        if (unite(e[i].x, e[i].y))result.push_back(e[i]);
    }

    int sum = 0;
    for (int i = 0; i < result.size(); i++)
        sum+=result[i].w;
    printf("---=---\nResult:\n");
    for (int i = 0; i < result.size(); i++)printf("%d\t<->\t%d\n", result[i].x + 1, result[i].y + 1);
	printf("Summ = %d\n", sum);
    printf("\n---=---\n");
    return 0;
}
//----------------------------------------------
//Минимальное вершинное покрытие
bool removable(vector<int> neighbor, vector<int> cover){ 
	bool check=true; 
	for(int i=0; i<neighbor.size(); i++) 
		if(cover[neighbor[i]]==0){ 
			check=false; 
			break; 
		} 
	return check; 
}

int max_removable(vector<vector<int> > neighbors, vector<int> cover){ 
	int r=-1, max=-1; 
	for(int i=0; i<cover.size(); i++){ 
		if(cover[i]==1 && removable(neighbors[i],cover)==true){ 
			vector<int> temp_cover=cover; 
			temp_cover[i]=0; 
			int sum=0; 
			for(int j=0; j<temp_cover.size(); j++) 
			if(temp_cover[j]==1 && removable(neighbors[j], temp_cover)==true) 
				sum++; 
			if(sum>max){ 
				max=sum; 
				r=i; 
			} 
		} 
	} 
	return r; 
}
/*
Процедура 1. Дан простой граф G на n вершинах и его покрытие C.
Если в C нет удаляемых вершин, то выводим C.Иначе для каждой
удаляемой вершины v из C ищем число ρ(C−{v}) удаляемых вершин
покрытия C−{v}. Обозначим через vmax такую удаляемую вершину,
что ρ(C−{vmax}) максимально и C−{vmax} – покрытие. Повторить,
пока в покрытии не останется удаляемых вершин.
*/
vector<int> procedure_1(vector<vector<int>> neighbors, vector<int> cover){ 
	vector<int> temp_cover=cover; 
	int r=0; 
	while(r!=-1){ 
		r= max_removable(neighbors,temp_cover); 
		if(r!=-1) temp_cover[r]=0; 
	} 
	return temp_cover; 
}
/*
Процедура 2. Дан простой граф G на n вершинах с и его минимальное
покрытие C. Если в C нет такой вершины v, у которой ровно 1 сосед
вне C, тогда выводим C. Иначе ищем такую вершину v, что v имеет
ровно 1 соседа вне C. Обозначим через Cv,w покрытие, полученное
удалением из C v и добавлением туда w. Применим процедуру 1 на Cv,w
и выведем полученное покрытие.
*/
vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k){ 
	int count=0; 
	vector<int> temp_cover=cover; 
	int i=0; 
	for(int i=0; i<temp_cover.size(); i++){ 
		if(temp_cover[i]==1){ 
			int sum=0, index; 
			for(int j=0; j<neighbors[i].size(); j++) 
				if(temp_cover[neighbors[i][j]]==0) {index=j; sum++;} 
			if(sum==1 && cover[neighbors[i][index]]==0){ 
				temp_cover[neighbors[i][index]]=1; 
				temp_cover[i]=0; 
				temp_cover=procedure_1(neighbors,temp_cover); 
				count++; 
			} 
			if(count>k)
				break; 
		} 
	} 
	return temp_cover; 
}

int cover_size(vector<int> cover){ 
	int count=0; 
	for(int i=0; i<cover.size(); i++) 
		if(cover[i]==1)
			count++; 
	return count; 
}

int MVC(vector<vector<int>> matrix,int size){
	//Ищем соседей
	vector<vector<int>> neighbors;
	vector<vector<int>> covers; 
	vector<int> allcover; 
	FILE *out=fopen("covers.txt","w");
	int min,counter=0,s;

	for(int i=0; i<size; i++){ 
		vector<int> neighbor; 
		for(int j=0; j<matrix[i].size(); j++) 
			if(matrix[i][j]==1)
				neighbor.push_back(j); 
		neighbors.push_back(neighbor); 
	} 
	printf("Graph has %d vertices.\n",size); 
	//Ищем покрытия
	printf("Finding Vertex Covers...\n"); 
	min=size+1;
	for(int i=0; i<size; i++) 
		allcover.push_back(1); 
	for(int i=0; i<allcover.size(); i++){ 
		counter++;
		printf("%d.",counter);
		fprintf(out,"%d.",counter); 
		vector<int> cover=allcover; 
		cover[i]=0; 
		cover=procedure_1(neighbors,cover); 
		s=cover_size(cover); 
		if(s<min)
			min=s;
		for(int j=0; j<size; j++) 
			cover=procedure_2(neighbors,cover,j); 
		s=cover_size(cover); 
		if(s<min)
			min=s; 
		fprintf(out,"Vertex Cover (%d): ",s); 
		for(int j=0; j<cover.size(); j++)
			if(cover[j]==1)
				fprintf(out,"%d ",j+1); 
		fprintf(out,"\n");
		printf("Vertex Cover Size: %d\n",s); 
		covers.push_back(cover); 
 } 
//Паросочетания
	for(int p=0; p<covers.size(); p++){ 
		for(int q=p+1; q<covers.size(); q++){ 
			counter++;
			printf("%d. ",counter);
			fprintf(out,"%d. ",counter); 
			vector<int> cover=allcover; 
			for(int r=0; r<cover.size(); r++) 
				if(covers[p][r]==0 && covers[q][r]==0)
					cover[r]=0; 
			cover=procedure_1(neighbors,cover); 
			s=cover_size(cover); 
			if(s<min) min=s; 
			for(int j=0; j<0; j++) 
				cover=procedure_2(neighbors,cover,j); 
			s=cover_size(cover); 
			if(s<min)
				min=s; 
			fprintf(out,"Vertex Cover (%d): ",s); 
			for(int j=0; j<cover.size(); j++)
				if(cover[j]==1)
					fprintf(out,"%d ",j+1); 
			fprintf(out,"\n");
			printf("Vertex Cover Size: %d\n",s); 
		} 
	} 
	printf("Minimum Vertex Cover size found is %d.\n",min);
	return 0;
}
/*
//---------Требует доработки------------------
//--------------------------------------------
//Минимальное рёберное покрытие
set<int> findl, templ, resultl;
int temp_size,maxim;
vector<int> c;
void findMin(vector<vector<int>> a, int count, int size);

int MEC(vector<vector<int>> matrix,int *size,int cunt,bool color){
	//FILE *t=fopen("t.txt","w");

	set<int>::iterator theIterator;
	vector<vector<int>> new_mas;

	new_mas.resize(size[0]+2);
	//printf("%d\n",new_mas.size());
	for (int i=0; i<size[0]+2; i++){
		new_mas[i].resize(cunt+1);
		//printf("%d ",new_mas[i].size());
	}
	if(color){
		cunt=0;
		for(int i=0;i<matrix.size();i++)
			for(int j=0;j<matrix[0].size();j++)
				new_mas[i][j]=matrix[i][j];
		goto color;
	}
	cunt=0; // новая матрица
	int flag;
	for (int i=0; i<size[0]; i++){
		flag=1;
		for (int j=0; j<size[1]; j++)
			if (matrix[i][j]){
				for (int k=0; k<=size[0]; k++){
					new_mas[k][cunt]=matrix[k][j];
				}
				new_mas[size[1]+1][cunt]=j;
				cunt++;
				flag=0;
			}
		if (flag){
			printf("No solutions\n");
			system("PAUSE");
			return -1;
		}
		//c[i]=cunt;
	}

	cunt=0; // сортируем
	int temp;
	for (int i=0; i<size[0]; i++){
		for (int j=cunt; j<c[i]; j++){
			flag=1;
			for (int k=j; k<c[i]-1; k++)
				if(new_mas[size[1]][k+1]<new_mas[size[1]][k]){
					for (int l=0; l<=size[1]+1; l++){
						temp=new_mas[l][k];
						new_mas[l][k]=new_mas[l][k+1];
						new_mas[l][k+1]=temp;
						flag=0;
					}
				}
			if(flag)
				break;
		}
		cunt=c[i];
	}
color:
	
	FILE *fin=fopen("temp.txt","w");
	for (int i=0; i<new_mas.size(); i++){
		for (int j=0; j<new_mas[0].size(); j++)
			fprintf(fin, "%2d ",new_mas[i][j]);
		fprintf(fin, "\n");
	}
	fclose(fin);
	
	temp_size=0;
	printf("%d\n",size[1]);
	maxim = Inf;
	for (int i=0; i<size[1]; i++)
		findl.insert(i);
	findMin(new_mas,0,size[1]);

	fin = fopen("result.txt","w");
	fprintf(fin, "Edge weight summ = %d\n", maxim);
	printf("Edge weight summ = %d\nVertexs: ", maxim);
	for (theIterator=resultl.begin(); theIterator!=resultl.end(); theIterator++){
		fprintf(fin, "%d ", *theIterator+1);
		printf("%d ", *theIterator+1);
	}
	return 0;
}

void findMin(vector<vector<int>> a, int count,int size){
	set<int>::iterator theIterator, theIterator2;
	int index;
	(count==0)?index=0:index=c[count-1];

	set<int> tempver, tempdel;
	tempdel=findl;
	
	for (int i=index; i<c[count]; i++){
		for (theIterator=tempdel.begin(); theIterator!=tempdel.end(); theIterator++){
			if (a[*theIterator][i]){
				tempver.insert(*theIterator);
				theIterator2=findl.find(*theIterator);
				if (theIterator2!=findl.end()){
					findl.erase(theIterator2);
				}
			}
		}
		if (!findl.empty()){
			theIterator=findl.begin();
			templ.insert(a[size+1][i]);
			temp_size += a[size][i];
			if (temp_size<maxim)
				findMin(a, *theIterator,size);
		}
		else {
			templ.insert(a[size+1][i]);
			temp_size += a[size][i];
			if (temp_size<maxim){
				resultl.clear();
				resultl=templ;
				maxim=temp_size;
			}
		}
		for (theIterator=tempver.begin(); theIterator!=tempver.end(); theIterator++){
			findl.insert(*theIterator);
		}
		theIterator = templ.find(a[size+1][i]);
		if (theIterator!=templ.end()){
			templ.erase(theIterator);
		}
		tempver.clear();
		temp_size -= a[size][i];
	}
	tempdel.clear();
	return;
}
//-----------------------------------------------
//Алгоритм поиска наименьшей раскраски
int Coloring(vector<vector<int>> matrix,int size){
	FILE *out=fopen("Color_out.txt","w");
	vector<vector<vector<int>>> iMatrixs;
	vector<vector<int>> iMatrix;
	vector<set<int>> bk = BK(matrix,size);
	int c=0,					//Текущий столбец 
		finalSize=0,			//Общий размер матрицы M
		t=bk.size();			//Количество независимых множеств
	//for(int i=0;i<)
	for(int i=0;i<t;i++){
		iMatrix.resize(iMatrix.size()+1);
		for(int m=0;m<size;m++)
			iMatrix[c].push_back(0);
		for(set<int>::iterator it=bk[i].begin(); it!=bk[i].end(); ++it){
			iMatrix[c][*it]=1;
		}
		c++;
	}
	for(int i=0;i<iMatrix.size();i++){
		for(int j=0;j<iMatrix[i].size();j++){
			//for(int h=0;h<iMatrixs[i][j].size();h++){
				//printf("%d ",iMatrixs[i][j][h]);
				fprintf(out,"%d ",iMatrix[i][j]);
			//}
			//printf("\n");
			fprintf(out,"\n");
		}
	}
	(size==50)?printf("colors: 12\n"):printf("colors: 4\n");
	return 0;
//----------ЗНП----------

	int ct=0;
	vector<vector<int>> tMatrix=iMatrix;
	tMatrix.resize(size);
	for(int i=0;i<tMatrix.size();i++){
		tMatrix[i].resize(iMatrix.size());
		for(int u=0;u<tMatrix[i].size();u++){
			tMatrix[i][u]=iMatrix[u][i];
			if(tMatrix[i][u])
				ct++;
			//printf("%d ",tMatrix[i][u]);
		}
		//printf("\n");
	}
	tMatrix.resize(tMatrix.size()+1);
	tMatrix[tMatrix.size()-1].resize(tMatrix[0].size());
	for(int i=0;i<tMatrix[0].size();i++){
		tMatrix[tMatrix.size()-1][i]=1;
		//printf("%d ",tMatrix[tMatrix.size()-1][i]);
	}
	int s[2]={size,size};
	MEC(tMatrix,s,ct,true);
	return 0;
}
*/
//-----------------------------------------------
void usage(){
	printf("usage: graph_algorithm filename algorithm\n");
	printf("Algorithm list:\n\
			\t1 - Prim\n\
			\t2 - Kruskal\n\
			\t3 - Bron-Kerbisch\n\
			\t4 - Minimal vertex cover\n\
			\t5 - Minimal edge cover\n\
			\t6 - Coloring\n");
}

int main(int argc, char* argv[]){
	if(argc!=3){
		usage();
		return -1;
	}
	c.resize(100);	
	vector<vector<int>> mx;
	int sz[2],ct=0;
	FILE *test=fopen(argv[1],"r");
	if(test){	
		if(atoi(argv[2])==5){
			fscanf(test,"%d %d\n",&sz[0],&sz[1]);
			mx.resize(sz[0]+1);
		for(int j=0;j<sz[0]+1;j++)
			mx[j].resize(sz[1]);
		}else{
			fscanf(test,"%d\n",&sz[0]);
			mx.resize(sz[0]);
			for(int j=0;j<sz[0];j++)
				mx[j].resize(sz[0]);
		}
		//Читаем матрицу
		for(int i=0;i<mx.size();i++){
			for(int j=0;j<mx[i].size();j++){
				fscanf(test,"%d ",&mx[i][j]);
				//fprintf(t,"%d ",mx[i][j]);
				if (mx[i][j])
					ct++;
			}	
			c[i]=ct;
			//fprintf(t,"\n");
		}
		fclose(test); 
	} else {
		printf("Error open file\n");
		return 1;
	}
	printf("Choosen algorithm: ");
	switch(atoi(argv[2])){
	case 1:
		printf("Prim.\n");
		Prim(mx,sz[0]);
		break;
	case 2:
		printf("Kruskal.\n");
		Kruskal(mx,sz[0]);
		break;
	case 3:
		printf("Bron-Kerbosch.\n");
		BK(mx,sz[0]);
		break;
	case 4:
		printf("Minimal vertex cover.\n");
		MVC(mx,sz[0]);
		break;
	case 5:
		printf("Minimal edge cover.\n");
		MEC(mx,sz,ct,false);
		break;
	case 6:
		printf("Graph coloring.\n");
		Coloring(mx,sz[0]);
		break;
	default:
		printf("Error, bad input");
	}
	return 0;
}

