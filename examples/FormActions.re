[@react.component]
let make = () => {
  let onSubmit = _ => ();

  let formProps =
    Hooks.useForm(~onSubmit, ~validate=LoginFormValidations.validate, ());

  let {Hooks.pristine, handleSubmit, form, valid} = formProps;

  let firstNameField = Hooks.useField(~name="firstName", ~form, ());
  let lastNameField = Hooks.useField(~name="lastName", ~form, ());

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
    </form>
    <hr />
    <div>
      <h3> {ReasonReact.string("First Name Field Props")} </h3>
      {ReasonReact.string(firstNameFieldStringified)}
    </div>
    <div>
      <h3> {ReasonReact.string("Last Name Field Props")} </h3>
      {ReasonReact.string(lastNameFieldStringified)}
    </div>
    <div>
      <h3> {ReasonReact.string("Form Props")} </h3>
      {ReasonReact.string(formPropsStringified)}
    </div>
  </div>;
};
