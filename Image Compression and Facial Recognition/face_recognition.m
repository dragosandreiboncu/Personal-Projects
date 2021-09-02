function [dist img_index] = face_recognition(path, M, A, EigFaces, Pr_Img)
    
    Matrix = double(rgb2gray(imread(path)));
    Vector = Matrix( : ) ;
    Vector = Vector - M ;
    
    PrTestImg = transpose( EigFaces ) * Vector ;
    %consideram prima distanta cea mai mica
    %apoi verificam restul imaginilor;
    %daca au distanta mai mica, inlocuim distanta
    %si setam indexul
    img_index = 1 ;
    dist = norm(Pr_Img(:,1) - PrTestImg) ;
    for i = 2:10
      dist_current = norm(Pr_Img(:,i) - PrTestImg) ;
      if( dist_current < dist )
        dist = dist_current ;
        img_index = i ;
      endif
    endfor
  
  
endfunction
