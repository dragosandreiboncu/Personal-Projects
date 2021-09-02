% computes the NC centroids corresponding to the given points using K-Means
function centroids = clustering_pc( points , NC )
  %alegem NC centroizi random :
  centroids = zeros( NC , size(points,2) ); 
  puncte_random = randperm( size(points,1) );
  centroids = points( puncte_random(1:NC) , :);
  
  indici = Grupari( points, centroids, NC );
  %initializam a doua functie pentru a o repeta asemenea
  %prin care vom calcula mai precis un nou centroid:
  function centroizi_noi = CentroiziNoi( points , indici , NC )
    centroizi_noi = zeros(NC,size(points,2));
    for i=1:NC
      PCI = points(indici==i,:);
      NPCI = size(PCI,1);
      % facem o medie a acestor puncte si setam centrul de masa:
centroizi_noi(i, :) = (1/NPCI)*[sum(PCI(:,1)) sum(PCI(:,2)) sum(PCI(:,3))];
    end
  end
  %avem un vector ce va retine continuu valorile centroizilor precedenti
  %si le va compara printr-un while cu cele noi
  old_centroids = zeros( NC , size(points,2) );
  while(old_centroids != centroids )
    old_centroids = centroids;
    indici = Grupari( points, centroids, NC);
    centroids = CentroiziNoi( points, indici, NC);
  end
  
end