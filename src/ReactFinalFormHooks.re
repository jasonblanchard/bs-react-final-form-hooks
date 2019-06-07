/*
 TODO: For now, we're just passing this through from useForm to useField as a JS object, so there's no type safety if the caller uses it directly.
 A better way to handle this is:

   1. Create a `form` record type with a jsConverter annotation
   2. Add all fields to this record type
   3. Pass this record object out to the caller by converting it to/from JS at the boundaries

 #2 has to be implemented fully for this to work so that useField gets the right object properties.
 */
type rffForm = Js.t({.});

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

/* TODO: Add all form render props */
[@bs.deriving jsConverter]
type formRenderProps = {
  pristine: bool,
  handleSubmit: ReactEvent.Form.t => unit,
  submitting: bool,
  form: rffForm,
  valid: bool,
};

let useForm = (~onSubmit, ~validate=?, ()) => {
  let options = {"onSubmit": onSubmit, "validate": validate};

  let renderProps = rffUseForm(options);
  /* Js.log(renderProps); */
  formRenderPropsFromJs(renderProps);
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
  let renderProps = rffUseField(name, form, validate);
  Js.log(renderProps);

  {
    input: fieldInputRenderPropsFromJs(renderProps##input),
    meta: fieldMetaRenderPropsFromJs(renderProps##meta),
  };
};
