function view_cost_vs_nc(file_points)
  points = load("-ascii",file_points);
  for i = 1:10
    cost(i) = compute_cost_pc( points, clustering_pc(points ,i) );
  end
  k = 1:10;
  plot(k,cost);
  
end

