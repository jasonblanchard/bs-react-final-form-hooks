[@react.component]
let make = () => {
  /* TODO: Figure out how to use a record instead of Js.Dict for `values`. */
  let onSubmit = values =>
    switch (values) {
    | None => Js.log("Invalid")
    | Some(values) =>
      let firstName = Js.Dict.get(values, "firstName");
      let lastName = Js.Dict.get(values, "lastName");
      Js.log({j|Called with first name: $firstName, last name: $lastName|j});
    };

  let formProps =
    ReactFinalFormHooks.useForm(
      ~onSubmit,
      ~validate=LoginFormValidations.validate,
      (),
    );
  
  let {ReactFinalFormHooks.pristine, handleSubmit, form, valid} = formProps;

  let firstNameField =
    ReactFinalFormHooks.useField(~name="firstName", ~form, ());
  let lastNameField =
    ReactFinalFormHooks.useField(
      ~name="lastName",
      ~form,
      ~validate=LoginFormValidations.validateLastName,
      (),
    );

  let firstNameFieldErrorMessage =
    switch (firstNameField.meta.touched, firstNameField.meta.valid) {
    | (true, false) => ReasonReact.string(firstNameField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let lastNameFieldErrorMessage =
    switch (lastNameField.meta.touched, lastNameField.meta.valid) {
    | (true, false) => ReasonReact.string(lastNameField.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
    };

  let disabled =
    switch (pristine, valid) {
    | (false, true) => false
    | (true, _) => true
    | (_, false) => true
    };

  let firstNameFieldStringified = FormPropsHelper.stringifyField(firstNameField);
  let lastNameFieldStringified = FormPropsHelper.stringifyField(lastNameField);
  let formPropsStringified = FormPropsHelper.stringifyForm(formProps);

  <div>
    <form onSubmit=handleSubmit>
      <div>
        <label htmlFor={firstNameField.input.name}>
          firstNameFieldErrorMessage
          <br />
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
          lastNameFieldErrorMessage
          <br />
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
    </form>
    <div>
      <h3>{ReasonReact.string("First Name Field Props")}</h3>
      {ReasonReact.string(firstNameFieldStringified)}
    </div>
    <div>
      <h3>{ReasonReact.string("Last Name Field Props")}</h3>
      {ReasonReact.string(lastNameFieldStringified)}
    </div>
    <div>
      <h3>{ReasonReact.string("Form Props")}</h3>
      {ReasonReact.string(formPropsStringified)}
    </div>
  </div>;
};
