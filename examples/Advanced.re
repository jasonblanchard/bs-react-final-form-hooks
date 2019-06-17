type formData = {
  .
  "firstName": option(string),
  "lastName": option(string)
};

let initialValues: formData = {
    "firstName": Some("gob"),
    "lastName": Some("bluth")
};

[@bs.deriving jsConverter]
type state = {
  submittedFirstName: option(string),
  submittedLastName: option(string),
};

type submitPayload = {
  firstName: option(string),
  lastName: option(string),
};

type action =
  | Submit(submitPayload);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | Submit(payload) => {
            submittedFirstName: payload.firstName,
            submittedLastName: payload.lastName,
          }
        },
      {submittedFirstName: Some(""), submittedLastName: Some("")},
    );

  // TODO: Prevent from compiling if don't supply type?
  let onSubmit = (values: formData) => {
    let firstName = values##firstName;
    let lastName = values##lastName;
    dispatch(Submit({firstName, lastName}));
  };

  let formProps =
    Hooks.useForm(~onSubmit, ~validate=LoginFormValidations.validate, ());

  let {Hooks.pristine, handleSubmit, form, valid} = formProps;

  let firstNameField =
    Hooks.useField(
      ~name="firstName",
      ~form,
      ~validate=LoginFormValidations.validateFirstName,
      (),
    );
  let lastNameField =
    Hooks.useField(
      ~name="lastName",
      ~form,
      ~validate=LoginFormValidations.validateLastName,
      (),
    );

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
      <button onClick={_ => form##initialize(initialValues)}>
        {ReasonReact.string("initialize")}
      </button>
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
      <div className="data"> {ReasonReact.string(formPropsStringified)} </div>
    </div>
    <div className="state">
      <h3> {ReasonReact.string("State")} </h3>
      <div className="data"> {ReasonReact.string(stateStringified)} </div>
    </div>
  </div>;
};
