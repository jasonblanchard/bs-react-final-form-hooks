let initialValues = Js.Dict.empty();
Js.Dict.set(initialValues, "firstName", "gob");
Js.Dict.set(initialValues, "lastName", "bluth");

[@bs.deriving jsConverter]
type state = {
  submittedFirstName: string,
  submittedLastName: string,
};

type submitPayload = {
  firstName: string,
  lastName: string
};

type action =
  | Submit(submitPayload);

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
    switch (action) {
  | Submit(payload) => {submittedFirstName: payload.firstName, submittedLastName: payload.lastName}
  }, {submittedFirstName: "", submittedLastName: "" });

  let onSubmit = values =>
    switch (values) {
      | None => ()
      | Some(data) => 
        let firstName = switch (Js.Dict.get(data, "firstName")) {
          | Some(s) => s
          | None => ""
        };

        let lastName = switch (Js.Dict.get(data, "lastName")) {
          | Some(s) => s
          | None => ""
        };

        dispatch(Submit({
          firstName,
          lastName
        }));
      };

  let formProps =
    Hooks.useForm(~onSubmit, ~validate=LoginFormValidations.validate, ());

  let {Hooks.pristine, handleSubmit, form, valid} = formProps;

  let firstNameField = Hooks.useField(~name="firstName", ~form, ~validate=LoginFormValidations.validateFirstName, ());
  let lastNameField = Hooks.useField(~name="lastName", ~form, ~validate=LoginFormValidations.validateLastName, ());

  let disabled =
    switch (pristine, valid) {
    | (false, true) => false
    | (true, _) => true
    | (_, false) => true
    };

  let firstNameFieldStringified =
    FormPropsHelper.stringifyField(firstNameField);
  let lastNameFieldStringified =
    FormPropsHelper.stringifyField(lastNameField);
  let formPropsStringified = FormPropsHelper.stringifyForm(formProps);

  let stateStringified =
    switch (Js.Json.stringifyAny(stateToJs(state))) {
      | Some(s) => s
      | None => ""
    };

  <div>
    <form onSubmit=handleSubmit>
      <div>
        <label htmlFor={firstNameField.input.name}>
          {ReasonReact.string("First Name")}
        </label>
        <input
          name={firstNameField.input.name}
          value={firstNameField.input.value}
          onChange={firstNameField.input.onChange}
          onBlur={firstNameField.input.onBlur}
          onFocus={firstNameField.input.onFocus}
          id={firstNameField.input.name}
        />
      </div>
      <div>
        <label htmlFor={lastNameField.input.name}>
          {ReasonReact.string("Last Name")}
        </label>
        <input
          name={lastNameField.input.name}
          value={lastNameField.input.value}
          onChange={lastNameField.input.onChange}
          onBlur={lastNameField.input.onBlur}
          onFocus={lastNameField.input.onFocus}
          id={lastNameField.input.name}
        />
      </div>
      <button disabled> {ReasonReact.string("submit")} </button>
      <button onClick={_ => form##reset(None)}>
        {ReasonReact.string("reset")}
      </button>
      <button onClick={_ => form##initialize(initialValues)} >{ReasonReact.string("initialize")}</button>
    </form>
    <hr />
    <div className="firstNameProps">
      <h3> {ReasonReact.string("First Name Field Props")} </h3>
      <div className="data">
        {ReasonReact.string(firstNameFieldStringified)}
      </div>
    </div>
    <div className="lastNameProps">
      <h3> {ReasonReact.string("Last Name Field Props")} </h3>
      <div className="data">
        {ReasonReact.string(lastNameFieldStringified)}
      </div>
    </div>
    <div className="formProps">
      <h3> {ReasonReact.string("Form Props")} </h3>
      <div className="data">
        {ReasonReact.string(formPropsStringified)}
      </div>
    </div>
    <div className="state">
      <h3>{ReasonReact.string("State")}</h3>
      <div className="data">
        {ReasonReact.string(stateStringified)}
      </div>
    </div>
  </div>;
};
