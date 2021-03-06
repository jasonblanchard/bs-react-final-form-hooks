[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let page =
    switch (url.path) {
    | [] => <HomePage />
    | ["simple"] =>
      <div>
        <h2> {ReasonReact.string("Simple Form")} </h2>
        <SimpleForm />
      </div>
    | ["advanced"] =>
      <div>
        <h2> {ReasonReact.string("Form Actions")} </h2>
        <Advanced />
      </div>
    | _ => <div> {ReasonReact.string("404")} </div>
    };

  <div> page </div>;
};
