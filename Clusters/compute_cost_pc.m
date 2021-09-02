% computes a clustering solution total cost
function cost = compute_cost_pc(points, centroids)
  
	cost = 0; 
	NC = size(centroids,1);
  indici = Grupari( points, centroids, NC );
  nr_puncte = size(points,1);
  
  for i=1:NC
    cost_curent = 0;
    for j=1:nr_puncte
      if(indici(j,1) == i)
        cost_curent += sqrt(sum((points(j,:) - centroids(i,:)) .^ 2));
      end
    end
    cost += cost_curent;
    
  end
 
end

