int nb_sommet(){
return 6*(6-1)/2;}

int est_adjacent(int u, int v){
 if(0< u && 0<v && u<nb_sommet()+1 && v<nb_sommet()+1){
  int i,j,index=1;
  int T[nb_sommet()+1];
  for(i=0;i<6-1;i++)
   for(j=i+1;j<6;j++)
    {
     T[index]= (1 << i) + (1 << j);
     index++;
    }
  return (!(T[u] & T[v]));
 }	
 else return 0;
}

