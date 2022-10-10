import React, { useState, useCallback, useEffect, useMemo } from "react";
import Button from "../../components/Button";
import ProfileModal from "../../components/Modals/ProfileModal";
import UserLayout from "../../others/UserLayout";
import Section from "../../components/Section";
import { Link, useLocation, useMatch, useResolvedPath, useNavigate} from "react-router-dom";
import axiosInstance from "../../configs/Axios";
import { routes } from "../../configs/Api";


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

const Profile = () => {


  const [openedModal, setOpenedModal] = useState(false);
  const [regShelter, setRegShelter] = useState([]);
  const [profile, setProfile] = useState({});


  const profileFields = [
    { key: "Name", value: profile.name },
    { key: "E-mail", value: profile.email },
    { key: "Phone", value: profile.phoneNumber },
  ];

  const EditProfile = useCallback(async () => {
    axiosInstance
      .post(routes.user.register, {
      })
      .then(({ data }) => setProfile(data));
  }, []);

  useEffect(() => {
    EditProfile();
  }, [EditProfile]);


  return (
    <UserLayout>
      <div className="title-background top-4 w-[52rem] h-24"/>
      <div className="table-background w-[52rem] h-[36rem]"/>
      <ProfileModal
        modalIsOpen={openedModal}
        closeModal={() => {
          setOpenedModal(false);
        }}
        submitForm={EditProfile}
      />
      <div className="absolute left-20 row-between1">
        <div className="flex items-center justify-between gap-2">
          <div className="big-text font-bold">
              Personal 
          </div>
          <div className="big-text font-bold">
              details 
          </div>
        </div>
        <Button onClick={() => setOpenedModal(true)}>
          <div className="button">
            Edit
          </div>
        </Button>
      </div>
      <div className="absolute top-24 left-9">
        <Section title={""} fields={profileFields} />
      </div>
      <div className="absolute left-[18rem] top-[26rem]">
        <Button>
            <div className="button">
              <div className="row-between2">
                <div>Resign</div><div>from</div><div>current</div><div>shelter</div>
              </div>
            </div>
        </Button>
      </div>
      <div className="absolute top-[31rem] left-[21rem]">
        <CustomLink to={"/"}>
          <div className="button row-between2">
            <div>Back</div><div>to</div><div>shelter</div><div>list</div>
          </div>
        </CustomLink>
        </div>
    </UserLayout>
  );
};

export default Profile;
