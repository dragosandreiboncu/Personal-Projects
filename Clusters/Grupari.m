function indici = Grupari( points , centroids , NC )
  
  indici = zeros( size(points,1) , 1 );
  linii_points = size(points,1);
  for i=1:linii_points
    centroidul_corespunzator = 1;
    distanta_min = sum((points(i,:) - centroids(1,:)) .^ 2);
    for j=2:NC
      distanta = sum((points(i,:) - centroids(j,:)) .^ 2);
      if(distanta < distanta_min)
        distanta_min = distanta;
        centroidul_corespunzator = j;
      end
    end
    indici(i) = centroidul_corespunzator;
  end
  
end