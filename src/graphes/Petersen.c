int nb_sommet(){
return 10;}

int est_adjacent(int u, int v){
 if(0< u && 0<v && u<11 && v<11){
  int i,j,index=1;
  int T[11];
  for(i=0;i<5;i++)
   for(j=i+1;j<5;j++)
    {
     T[index]= (1 << i) + (1 << j);
     index++;
    }
  return (!(T[u] & T[v]));
 }	
 else return 0;
}


