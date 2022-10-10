import React from "react";
import { Link, useMatch, useResolvedPath  } from "react-router-dom";
import Avatar from "react-avatar";
import logo from "../logo.svg";
import { useAuth0 } from "@auth0/auth0-react";

export function CustomLink({ children, to, ...props }) {
  const resolved = useResolvedPath(to);
  const match = useMatch({ path: resolved.pathname, end: true });

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


const UserMenu = () => {
  const { logout, user } = useAuth0();

  return (
    <div>
      <div className="left-green-background"/>
      <div className="left-menu">
          <img src={logo} alt="StandingTogether logo" />
        <div className="bottom-info">
          <div className="sign-out">
          <Link
            className="signout"
            to="/"
            onClick={() => {
              logout({ returnTo: window.location.origin });
            }}
          >
            Signout
          </Link>

          </div>
          <Avatar name={user.nickname} round="100px" size="50px" />
          <div className="name-info">
            <Link to="/profile">
              {user.nickname}
            </Link>
          </div>
        </div>
      </div>
    </div>
  );
};

export default UserMenu;
