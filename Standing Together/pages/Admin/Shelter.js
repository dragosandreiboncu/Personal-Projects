import React, { useState, useMemo, useEffect, useCallback } from "react";
import Button from "../../components/Button";
import AdminLayout from "../../others/AdminLayout";
import AddModal from "../../components/Modals/AddModal";
import Table from "../../components/Table";
import Section from "../../components/Section";
import { Link, useLocation, useMatch, useResolvedPath } from "react-router-dom";

export function CustomLink({ children, to, ...props }) {
  const resolved = useResolvedPath(to);
  const location = useLocation();
  const match =
    useMatch({ path: resolved.pathname, end: true }) ??
    location.pathname.includes(to);

  return (
    <div>
      <Link
        to={to}
        {...props}
        className={"nav-link" + (match ? " active" : "")}
      >
        {children}
      </Link>
    </div>
  );
}

const columns = [
  {
    Header: "E-mail",
    accessor: "email",
  },
  {
    Header: "Phone number",
    accessor: "phoneNumber",
  },
];

const Shelter = () => {

  const [openedModal, setOpenedModal] = useState(false);
  const [shelterInfo, setInfo] = useState({});
  const [metricsInfo, setMetricsData] = useState({});

  const { pathname } = useLocation();
  const id = pathname.split("/").reverse()[0];

  const generalDetails = useMemo(
    () => [
      { key: "Capacity", value: shelterInfo.capacity },
      { key: "Accept Pets", value: shelterInfo.acceptPets === true ? "Yes" : "No" },
      { key: "Offers food", value: shelterInfo.offersFood === true ? "Yes" : "No"  },
      { key: "Offers first aid", value: shelterInfo.offersFirstAid === true ? "Yes" : "No"  },
    ],
    [shelterInfo]
  );

  return (
    <AdminLayout>
      <AddModal
        modalIsOpen={openedModal}
        closeModal={() => {
          setOpenedModal(false);
        }}
      />
      <div className="address-background absolute w-screen h-16 left-[-3.5rem] top-[-0.5rem]"/>
      <div className="title-background top-8 w-[57rem] h-12"/>
      <div className="table-background absolute top-20 w-[57rem] h-[25rem]"/>
      <div className="absolute top-[-2rem] left-[-2rem] row-between1 big-text font-bold">
        Address...
      </div>
      <div className="absolute top-[2.25rem] left-4 row-between1">
        <div className="row-between2">
            <div className="text-3xl font-bold">
              General
            </div>
            <div className="text-3xl font-bold">
              details 
            </div>
        </div>
      </div>
      <div className="absolute top-[2.4rem] left-[46rem]" >
          <Button onClick={() => setOpenedModal(true)}>
            Edit
          </Button>
      </div>
      <div className="absolute top-[2.4rem] left-[51rem]" >
        <Button className="delete-button">
          <CustomLink to={"/admin"}>
            Delete
          </CustomLink>
        </Button>
      </div>
      <div className="absolute top-20 left-4">
        <Section title={""} fields={generalDetails} />
      </div>
      <div className="title-background top-[32rem] w-[57rem] h-12"/>
      <div className="absolute top-[32.25rem] left-4 row-between1">
        <div className="row-between2">
            <div className="text-3xl font-bold">
              Recent
            </div>
            <div className="text-3xl font-bold">
              residents 
            </div>
            <div className="text-3xl font-bold">
              registered 
            </div>
        </div>
      </div>
      <div className="address-background absolute w-[57rem] h-[6.6rem] top-[35rem]"/>
      <div className="table-background absolute top-[41.6rem] w-[57rem] h-[20rem]"/>
      <div className="absolute top-[35rem]" >
          <Table data={[]} columns={columns} noHref={2}/>
      </div>

    </AdminLayout>
  );
};

export default Shelter;
