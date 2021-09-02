function A = task1( image_name , k )
  
  A = imread( image_name ) ;
  [ U ,S ,V ] = svd( A ) ;
  
  %eliminam valorile ce nu sunt necesare la compresie
  S( k + 1:end , : ) = 0 ;
  S( : , k + 1:end ) = 0 ;

  A = U * S * transpose( V ) ;
  
end