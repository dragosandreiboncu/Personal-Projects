import React, { useState, useEffect, useCallback } from "react";
import Button from "../../components/Button";
import Table from "../../components/Table";
import AdminLayout from "../../others/AdminLayout";
import AddModal from "../../components/Modals/AddModal";
import { routes } from "../../configs/Api";
import axiosInstance from "../../configs/Axios";


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
  const [openedModal, setOpenedModal] = useState(false);

  const handleAddShelter = (form) => {
    (async () => {
      axiosInstance
        .post(routes.admin.addShelter, form)
        .then();
    })();
  };
  
  useEffect(() => {
  }, []);

  return (
    <AdminLayout>
      <AddModal
        modalIsOpen={openedModal}
        closeModal={() => {
          setOpenedModal(false);
        }}
        submitForm={handleAddShelter}
      />
        <div className="text-4xl" >
          Shelters
        </div>
        <div className="absolute top-[-2rem] left-[47.5rem]" >
          <Button onClick={() => setOpenedModal(true)}>
          <div className="button row-between2">
            <div>Add</div><div>new</div><div>shelter</div>
          </div>
          </Button>
        </div>
        <div className="title-background top-10 w-[60.25rem] h-[6.6rem]"/>
        <div className="table-background w-[60.25rem] h-[34rem]"/>
        <div className="absolute top-10" >
          <Table data={shelters} columns={columns} noHref={1}/>
        </div>
    </AdminLayout>
  );
};

export default Shelters;
