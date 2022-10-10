import React from "react";
import { Link } from "react-router-dom";
import Avatar from "react-avatar";
import logo from "../logo.svg";
import { useAuth0 } from "@auth0/auth0-react";

const AdminMenu = () => {
  const { logout, user } = useAuth0();

  return (
    <div>
      <div className="left-green-background"/>
      <div className="left-menu">
          <img src={logo} alt="StandingTogether logo" />
        <div className="bottom-info">
          <div className="sign-out">
            <Link to="/" onClick={() => {
              logout({ returnTo: window.location.origin });
            }}
            >
              Sign out
            </Link>
          </div>
          <Avatar name={"A"} round="100px" size="50px" />
          <div className="admin-name-info">
              ADMIN
          </div>
        </div>
      </div>
    </div>
  );
};

export default AdminMenu;
