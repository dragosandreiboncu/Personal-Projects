function [A S] = task4( image_name , k )
  A = double( imread( image_name ) ) ;
  m = size(A, 1) ;
  n = size(A, 2) ;
  
  M = mean(A, 2) ;
  A = A - M ;

  Z = A * ( transpose( A ) ./ (n-1) ) ;

  [V S] = eig(Z) ;
  if( k < size(V, 2) )
    W(:,1:k) = V( :, 1:k) ;
  endif
  if( k >= size(V, 2) )
    W = V ;
  endif
  Y = transpose( W ) * A ;
  A = W * Y + M  ;
   
endfunction