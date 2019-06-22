#include <stdio.h>
#include <stdlib.h>

#define KOSU 48 //人間の数
#define BUFSIZE 20
#define MAXQUEUE 2500

//キュー（構造体）
struct queue{
  char data[MAXQUEUE];
  int head;
  int tail;
};

//最短経路を記憶する
int *saitankeiro;

//行列。yornで1か0か、checkで一度見たかを数える。（構造体）
typedef struct gyoretsu{
  int yorn = 0;
  int check = 0;
}gyoretsu;

FILE *fpin, *fpout;
gyoretsu a[KOSU][KOSU];
int counter = 0;

//キューの初期化（関数）
void initialize (struct queue *q){
  int i;
  q->head = 0;
  q->tail = 0;
  for (i = 0; i < MAZQUEUE; i++){
    q->data[i] = ' ';
  }
}

//キューに一つデータを入れる（関数）
void enqueue (struct queue *q, int item){
  if (q->tail >= MAXQUEUE){
    printf ("This queue is full\n");
  }
  else{
    q->data[q->tail] = item;
    q->tail++;
  }
}

//キューから一番前のデータを出す（関数）
void dequeue (struct queue *q){
  int tmp;
  if (q->head == q->tail){
    return -1;
  }
  else{
    tmp = q->data[q->head];
    q->head++;
    return tmp;
  }
}

/*//指定されたところを見てキューに入れる（関数）
void lookandput (FILE *fp, int id, struct queue q){
  int i;
  for (i = 0; i < KOSU; i++){
    if (a[id][i].yorn == 1){
      if (a[id][i].check == 0){
	enqueue (&q, a[id][i]);
        a[id][i].check = 1;
      }
    }
  }
  }*/

//キューに出し入れし、最短経路を探す（関数）
void queue (){
  
}

//隣接行列を作る（関数）
void putgraph (FILE *fp){
  //printf ("putgraph started\n");
  char buf[BUFSIZE];
  int n;
  int x, y;
  int from, to;

  /*//aを初期化
  for (x = 0; x < KOSU; x++){
    for (y = 0; y < KOSU; y++){
      a[x][y].yorn = 0;
	}
	}*/

  //リンクがあるところを1にする
  for (n = 0; n < KOSU * (KOSU - 1); n++){
    //printf ("for started\n");
    if (fgets (buf, BUFSIZE-1, fp) != NULL){
      // printf ("if started\n");
      from = (int)strtol (strtok (buf, "\t"), NULL, 10);
      to = (int)strtol (strtok (NULL, "\n"), NULL, 10);
      a[from][to].yorn = 1;
      //printf ("%d\n",a[from][to]);
    }
    else{
      //printf ("else started\n");
      break;
    }
  }
  
}

//隣接行列をかく（関数）
void drawgraph (FILE *fp){
  int i, j;
  // printf ("drawgraph started\n");
  for (i = 0; i < KOSU; i++){
    //printf ("for1 started\n");
    fprintf (fp, "\n");
    //printf ("for1 finished\n");
    for (j = 0; j < KOSU; j++){
      //printf ("for2 started\n");
       fprintf (fp, "%d ", a[i][j].yorn);
       // printf ("%d ",a[i][j]);
    }
  }
}

/*//ファイルを開く（関数）
void FileOpen (char filename, char mode){
  if ((fpin = fopen (&filename, "mode")) == NULL){
    perror (&filename);
    exit (EXIT_FAILURE);
  }
  }*/

//ファイルを閉じる（関数）
void FileClose (FILE *fp){
  if (EOF == fclose (fp)){
    perror (fp);
    exit (EXIT_FAILURE);
  }
  //printf ("closed\n");
}

      

//main関数
int main (int argc, char *argv[], int myid, int yourid){
  int i, f;
  struct queue Q;
  int h, item;

  //main引数エラー処理
  if (argc != 5){
    fprintf (stderr, "Usage: <filename> <filename> <number> <number>\n");
    exit (EXIT_FAILURE);
  }

  //ファイルを開く
  if ((fpin = fopen (argv[1], "r")) == NULL){
    perror (argv[1]);
    exit (EXIT_FAILURE);
  }
  if ((fpout = fopen (argv[2], "w+")) == NULL){
    perror (argv[2]);
    exit (EXIT_FAILURE);
  }
  /*FileOpen (*argv[1], 'r');
    FileOpen (*argv[2], 'w');*/

  //最短経路を記憶するためのメモリ確保
  if ((saitankeiro = malloc (sizeof (int) * KOSU)) == NULL){
    perror (saitankeiro);
    exit (EXIT_FAILURE);
  }

  //ファイルの内容を行列に入れる
  putgraph (fpin);
  //printf ("putgraph done\n");

  //ファイルに書き込む
  drawgraph (fpout);
  //printf ("drawgraph done\n");

  //ファイルを閉じる
  FileClose (fpin);

  initialize (&Q);//キュー初期化
  enqueue (&Q, myid);//自分をキューに入れる
  dequeue (&Q);//一つキューから出す
  // lookandput (fpout, myid, Q);//キューに要素を入れる
  
  
  FileClose (fpout);//ファイルを閉じる

  free (saitankeiro);

}
