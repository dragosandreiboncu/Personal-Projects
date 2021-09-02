% outputs a graphical representation of the clustering solution
function view_clusters(points, centroids)
    NC = size(centroids,1);
    indici = Grupari( points , centroids , NC );
    for i=1:NC
      for j=1:size(points,1)
        if( indici(j,1) == 1 )
	        scatter3(points(j, 1), points(j, 2), points(j, 3), 'y');
          hold on;
        end
        
        if( indici(j,1) == 2 )
          scatter3(points(j, 1), points(j, 2), points(j, 3), 'b');
          hold on;
        end
        
        if( indici(j,1) == 3 )
          scatter3(points(j, 1), points(j, 2), points(j, 3), 'g');
          hold on;
        end
        
      end
    end
    
    
end

