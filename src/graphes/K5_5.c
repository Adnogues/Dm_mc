int nb_sommet(){
return 10;}

int est_adjacent(int u, int v){
 if(0< u && 0<v && u<11 && v<11){
  return (u<6 && v>5);
 }	
 else return 0;
}
