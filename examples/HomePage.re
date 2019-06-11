let handleClick = (path, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReactRouter.push(path);
};

[@react.component]
let make = () => {
  let handleClickSimple = handleClick("/simple");
  let handleClickFormActions = handleClick("/actions");

  <div>
    <ul>
      <li>
        <a href="#" onClick=handleClickSimple>
          {ReasonReact.string("Simple Example")}
        </a>
      </li>
      <li>
        <a href="#" onClick=handleClickFormActions>
          {ReasonReact.string("Form Actions")}
        </a>
      </li>
    </ul>
  </div>;
};
