function [ M A EigFaces Pr_Img ] = eigenface_core( path )
  %luam fiecare matrice a pozei
  %o tranformam intr-un Vector coloana
  %apoi fiecare Vector il punem unul langa altul in matricea T
  for i = 1:10
    Matrix = double(rgb2gray(imread(sprintf( '%s/%d.jpg', path, i))));
    Vector = double(Matrix( : )) ;
    T( :, i ) = Vector ;
  endfor
  M = mean( T, 2) ;
  A = T - M ;
  %values sunt valorile proprii puse pe diagonala unei
  %matrici goale, iar v_values o matrice ce contine pe 
  %fiecare coloana vectorul propriu X al valorii proprii X 
  [v_values values] = eig(transpose( A ) * A) ;
  %pentru fiecare valoare proprie >1 luam vectorul corespunzator
  %si il punem intr-o matrice V, pe coloana
  j = 1 ;
  for i = 1:size(values, 1 )
    if( values(i,i) > 1 )
      V(:,j) = v_values(:,i) ;
      j++ ;
    endif
  endfor
  
  EigFaces = A * V ;
  Pr_Img = transpose( EigFaces ) * A ;
endfunction