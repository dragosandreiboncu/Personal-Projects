import React, { useState, useMemo, useEffect, useCallback } from "react";
import Button from "../../components/Button";
import UserLayout from "../../others/UserLayout";
import RentModal from "../../components/Modals/RentModal";
import Section from "../../components/Section";
import { Link, useLocation, useMatch, useResolvedPath, useNavigate} from "react-router-dom";


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
  

const Shelter = () => {

  const [openedModal, setOpenedModal] = useState(false);
  const [shelterInfo, setInfo] = useState({});
  const [metricsInfo, setMetricsData] = useState({});

  const { pathname } = useLocation();
  const id = pathname.split("/").reverse()[0];

  const generalDetails = useMemo(
    () => [
      { key: "Occupancy", value: shelterInfo.capacity },
      { key: "Accept Pets", value: shelterInfo.acceptPets === true ? "Yes" : "No" },
      { key: "Offers food", value: shelterInfo.offersFood === true ? "Yes" : "No"  },
      { key: "Offers first aid", value: shelterInfo.offersFirstAid === true ? "Yes" : "No"  },
    ],
    [shelterInfo]
  );

  return (
    <UserLayout>
      <div className="address-background absolute w-screen h-16 left-[-3.5rem] top-[-0.5rem]"/>
      <div className="title-background top-12 w-[57rem] h-16"/>
      <div className="table-background absolute top-28 w-[57rem] h-[30rem]"/>
      <div className="absolute top-[-2rem] left-[-2rem] row-between1 big-text font-bold">
        Address...
      </div>
      <RentModal
        modalIsOpen={openedModal}
        closeModal={() => {
          setOpenedModal(false);
        }}
      />
      <div className="absolute top-[3.5rem] left-20 row-between1">
        <div className="row-between2">
            <div className="big-text font-bold">
              General
            </div>
            <div className="big-text font-bold">
              details 
            </div>
        </div>
      </div>

      <div className="absolute top-28 left-4">
        <Section title={""} fields={generalDetails} />
        <div className="absolute top-[25rem] left-[2rem]">
        <Button onClick={() => setOpenedModal(true)}>
          Sign up for shelter
        </Button>
        </div>
        <div className="absolute top-[25rem] left-[40rem]">
        <CustomLink to={"/"}>
          <div className="button row-between2">
            <div>Back</div><div>to</div><div>shelter</div><div>list</div>
          </div>
        </CustomLink>
        </div>
      </div>

    </UserLayout>
  );
};

export default Shelter;
