
[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let page = switch (url.path) {
    | ["simple"] => <div><h2> {ReasonReact.string("Simple Form")} </h2> <SimpleForm /> </div>
    | ["actions"] => <div><h2> {ReasonReact.string("Form Actions")} </h2> <FormActions /> </div>
    | _ => <div>{ReasonReact.string("404")}</div>
  };

  <div>{page}</div>;
};
