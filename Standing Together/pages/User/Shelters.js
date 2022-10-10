import React, { useState, useEffect, useCallback } from "react";
import Table from "../../components/Table";
import UserLayout from "../../others/UserLayout";

const columns = [
  {
    Header: "Address",
    accessor: "address",
  },
  {
    Header: "Occupancy",
    accessor: "occupancy"
  },
  {
    Header: "Food",
    accessor: "food",
    Cell: ({ value }) => (value === true ? "Yes" : "No"),
  },
  {
    Header: "First aid",
    accessor: "firstAid",
    Cell: ({ value }) => (value === true ? "Yes" : "No"),
  },
  {
    Header: "Pets",
    accessor: "pets",
    Cell: ({ value }) => (value === true ? "Yes" : "No"),
  },
];

const Shelters = () => {

  const [shelters, setShelters] = useState([]);

  return (
    <UserLayout>
        <div className="big-text" >
          Shelters
        </div>
        <div className="title-background top-10 w-[60.25rem] h-[6.6rem]"/>
        <div className="table-background w-[60.25rem] h-[34rem]"/>
        <div className="absolute top-10" >
          <Table data={shelters} columns={columns} noHref={0} />
        </div>
    </UserLayout>
  );
};

export default Shelters;
