import React from "react";
import { useNavigate } from "react-router-dom";
import { useTable } from "react-table/dist/react-table.development";

const Table = ({ data, columns, noHref }) => {
  const navigate = useNavigate();

  const { getTableProps, getTableBodyProps, headerGroups, rows, prepareRow } =
    useTable({
      columns,
      data,
    });

  const handleRowClick = (id) => {
    if(noHref === 0) navigate(`/shelters${id}`); if(noHref === 1) navigate(`/admin/shelter${id}`);
  };

  return (
    <table {...getTableProps()}>
      {(noHref===1 || noHref===0) && (
      <thead>
        {headerGroups.map((headerGroup) => (
          <tr1 {...headerGroup.getHeaderGroupProps()}>
            {headerGroup.headers.map((column) => (
              <th {...column.getHeaderProps()}>{column.render("Header")}</th>
            ))}
          </tr1>
        ))}
      </thead>
      )}
      {noHref===2 && (
      <thead>
        {headerGroups.map((headerGroup) => (
          <tr2 {...headerGroup.getHeaderGroupProps()}>
            {headerGroup.headers.map((column) => (
              <th {...column.getHeaderProps()}>{column.render("Header")}</th>
            ))}
          </tr2>
        ))}
      </thead>
      )}
      {(noHref===1 || noHref===0) && (
      <tbody {...getTableBodyProps()}>
        {rows.map((row) => {
          prepareRow(row);
          return (
            <tr1
              {...row.getRowProps()}
              key={row.id}
              className="cursor-pointer hover:bg-gray-50"
              onClick={() => handleRowClick(row.original.id)}
            >
              {row.cells.map((cell) => {
                return <td {...cell.getCellProps()}>{cell.render("Cell")}</td>;
              })}
            </tr1>
          );
        })}
      </tbody>
      )}
      {noHref===2 && (
      <tbody {...getTableBodyProps()}>
        {rows.map((row) => {
          prepareRow(row);
          return (
            <tr2
              {...row.getRowProps()}
              key={row.id}
              className="cursor-pointer hover:bg-gray-50"
              onClick={() => handleRowClick(row.original.id)}
            >
              {row.cells.map((cell) => {
                return <td {...cell.getCellProps()}>{cell.render("Cell")}</td>;
              })}
            </tr2>
          );
        })}
      </tbody>
      )}
    </table>
  );
};

export default Table;
