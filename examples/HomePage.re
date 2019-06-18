let handleClick = (path, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReactRouter.push(path);
};

[@react.component]
let make = () => {
  let handleClickSimple = handleClick("/simple");
  let handleClickFormActions = handleClick("/advanced");

  <div>
    <ul>
      <li>
        <a href="#" onClick=handleClickSimple>
          {ReasonReact.string("Simple Example")}
        </a>
      </li>
      <li>
        <a href="#" onClick=handleClickFormActions>
          {ReasonReact.string("Advanced Example")}
        </a>
      </li>
    </ul>
  </div>;
};
