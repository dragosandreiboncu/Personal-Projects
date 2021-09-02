function task5()
  %primul grafic
  Matrix = double( imread('in/images/image3.gif') ) ;
  [m, n] = size( Matrix ) ;
  [Matrix S] = task3('in/images/image3.gif', m) ;
  for i = 1:m
    Singular( i ) = S(i, i) ;
  endfor
  k( 1:m ) = 1:m ;
  plot(k, Singular) ;
  figure() ;
  %al doilea grafic
  for i = 1:m
    Suma( i ) = sum( Singular(1, 1:i) ) ;
  endfor
  Suma2 = sum( Singular(1, 1:min(m, n)) ) ;
  Raport( 1:m ) = Suma( 1:m ) / Suma2 ;
  plot(k, Raport) ;
  figure() ;
  %al treilea grafic
  for i = 1:m
    A = task1('in/images/image3.gif', i) ;
    Suma( i ) = 0 ;
    for j = 1:m
      for l = 1:n
        Suma( i ) += ( A(j, l) - Matrix(j, l) )^2 ;
      endfor
    endfor
    Suma3( i ) = Suma( i ) / (m * n) ;
  endfor
  plot(k, Suma3) ;
  figure() ;
  %al patrulea grafic
  for i = 1:m
    Suma( i ) = (2 * i + 1) / n ;
  endfor
  plot(k, Suma) ;
 
endfunction