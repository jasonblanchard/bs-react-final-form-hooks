type rffForm = Js.t({
  .
  batch: unit => unit,
  blur: unit => unit,
  change: unit => unit,
  focus: unit => unit,
  getFieldState: string => option(string),
  getRegisteredFields: unit => unit,
  getState: unit => unit,
  initialize: unit => unit,
  isValidationPaused: unit => unit,
  mutators: Js.t({.}),
  pauseValidation: unit => unit,
  registerField: unit => unit,
  reset: option(Js.t({.})) => unit,
  resumeValidation: unit => unit,
  setConfig: unit => unit,
  submit: unit => unit,
  subscribe: unit => unit
});

type rffUseFormOptions = {
  .
  "validate": option(Js.Dict.t(string) => Js.Dict.t(string)),
  "onSubmit": option(Js.Dict.t(string)) => unit,
};

/* TODO: Add all form render props */
type rffFormRenderProps = {
  .
  "pristine": bool,
  "handleSubmit": ReactEvent.Form.t => unit,
  "submitting": bool,
  "form": rffForm,
  "valid": bool,
};

[@bs.module "react-final-form-hooks"]
external rffUseForm: rffUseFormOptions => rffFormRenderProps = "useForm";

[@bs.deriving jsConverter]
type form = {
  batch: unit => unit,
  blur: unit => unit,
  change: unit => unit,
  focus: unit => unit,
  getFieldState: string => option(string),
  getRegisteredFields: unit => unit,
  getState: unit => unit,
  initialize: unit => unit,
  isValidationPaused: unit => unit,
  mutators: Js.t({.}),
  pauseValidation: unit => unit,
  registerField: unit => unit,
  reset: option(Js.t({.})) => unit,
  resumeValidation: unit => unit,
  setConfig: unit => unit,
  submit: unit => unit,
  subscribe: unit => unit
};

/* TODO: Add all form render props */
[@bs.deriving jsConverter]
type formRenderProps = {
  pristine: bool,
  handleSubmit: ReactEvent.Form.t => unit,
  submitting: bool,
  form: form,
  valid: bool,
};

let useForm = (~onSubmit, ~validate=?, ()) => {
  let options = {"onSubmit": onSubmit, "validate": validate};

  let renderProps = rffUseForm(options);

  {
    pristine: renderProps##pristine,
    handleSubmit: renderProps##handleSubmit,
    submitting: renderProps##submitting,
    form: formFromJs(renderProps##form),
    valid: renderProps##valid
  };
};

type rffFieldInputRenderProps = {
  .
  "name": string,
  "value": string,
  "onChange": ReactEvent.Form.t => unit,
  "onBlur": ReactEvent.Focus.t => unit,
  "onFocus": ReactEvent.Focus.t => unit,
};

/* TODO: Add all field meta props */
type rffFieldMetaRenderProps = {
  .
  "touched": bool,
  "valid": bool,
  "error": string
};

type rffFieldRenderProps = {
  .
  "input": rffFieldInputRenderProps,
  "meta": rffFieldMetaRenderProps,
};

type rffFieldValidateFn = option(option(string) => option(string));

[@bs.module "react-final-form-hooks"]
external rffUseField:
  (string, rffForm, rffFieldValidateFn) => rffFieldRenderProps =
  "useField";


[@bs.deriving jsConverter]
type fieldInputRenderProps = {
  name: string,
  value: string,
  onChange: ReactEvent.Form.t => unit,
  onBlur: ReactEvent.Focus.t => unit,
  onFocus: ReactEvent.Focus.t => unit,
};

/* TODO: Add all field meta props */
[@bs.deriving jsConverter]
type fieldMetaRenderProps = {
  touched: bool,
  valid: bool,
  error: string
};

type fieldRenderProps = {
  input: fieldInputRenderProps,
  meta: fieldMetaRenderProps,
};

let useField = (~name, ~form, ~validate=?, ()) => {
  let renderProps = rffUseField(name, formToJs(form), validate);
  /* Js.log(renderProps); */

  {
    input: fieldInputRenderPropsFromJs(renderProps##input),
    meta: fieldMetaRenderPropsFromJs(renderProps##meta),
  };
};
