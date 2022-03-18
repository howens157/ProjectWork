import { Link } from "react-router-dom";

const Header = () => {
    return (
        <ul className="nav">
        <Link className="home" to="/">jeopardy! topics</Link>
        <ul className="links">
            <li><Link to="/stats">stats</Link></li>
            <li><Link to="/stats">settings</Link></li>
            <li><Link to="/stats">profile</Link></li>
        </ul>
        </ul>
    );
}
export default Header;