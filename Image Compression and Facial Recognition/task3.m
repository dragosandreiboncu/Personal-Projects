function [ A S ] = task3( image_name , k )
  A = double( imread( image_name ) ) ;
  m = size(A, 1) ;
  n = size(A, 2) ;
  %mean face media; argumentul 2 pentru media pe linii
  %si 1 pentru coloane
  M = mean(A, 2) ;
  A = A - M ;
  
  Z = transpose( A ) ./ sqrt(n-1) ;
  [ U ,S ,V ] = svd( Z ) ;
  Z = U * S * transpose( V ) ;
  
  if( k < size(V, 2) )
    W(:, 1:k) = V(:, 1:k) ;
  endif
  if( k >= size(V, 2) )
    W = V ;
  endif
  
  Y = transpose( W ) * A ;
  A = W * Y + M  ;
endfunction