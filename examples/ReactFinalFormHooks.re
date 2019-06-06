type rffForm = Js.t({
  .
});

type rffUseFormOptions = Js.t({
  .
  validate: option(Js.Dict.t(string) => Js.Dict.t(string)),
  onSubmit: option(Js.Dict.t(string)) => unit,
});

type rffFormRenderProps = Js.t({
  .
  pristine: bool,
  handleSubmit: ReactEvent.Form.t => unit,
  submitting: bool,
  form: rffForm,
  valid: bool
});

[@bs.module "react-final-form-hooks"] external rffUseForm : rffUseFormOptions => rffFormRenderProps = "useForm"

[@bs.deriving jsConverter]
type formRenderProps = {
  pristine: bool,
  handleSubmit: ReactEvent.Form.t => unit,
  submitting: bool,
  form: rffForm,
  valid: bool
};

let useForm = (~onSubmit, ~validate=?, ()) => {
    let options = [%bs.obj {
      onSubmit: onSubmit,
      validate: validate
    }];

    let renderProps = rffUseForm(options);
    // Js.log(renderProps);
    formRenderPropsFromJs(renderProps);
};

type rffFieldInputProps = Js.t({
  .
  name: string,
  value: string,
  onChange: ReactEvent.Form.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
  onFocus: ReactEvent.Focus.t => unit
})

type rffFieldMetaProps = Js.t({
  .
  touched: bool,
  valid: bool
});

type rffFieldRenderProps = Js.t({
  .
  input: rffFieldInputProps,
  meta: rffFieldMetaProps
});

type rffFieldValidator = option(option(string) => option(string));

[@bs.module "react-final-form-hooks"] external rffUseField : (string, rffForm, rffFieldValidator) => rffFieldRenderProps = "useField";

[@bs.deriving jsConverter]
type fieldInputProps = {
  name: string,
  value: string,
  onChange: ReactEvent.Form.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
  onFocus: ReactEvent.Focus.t => unit
};

[@bs.deriving jsConverter]
type fieldMetaProps = {
  touched: bool,
  valid: bool
};

type fieldRenderProps = {
  input: fieldInputProps,
  meta: fieldMetaProps
}

let useField = (~name, ~form, ~validate=?, ()) => {
  let renderProps = rffUseField(name, form, validate);
  // Js.log(renderProps);

  {
    input: fieldInputPropsFromJs(renderProps##input),
    meta: fieldMetaPropsFromJs(renderProps##meta)
  }
}