function getData(selector) {
  return new Cypress.Promise((resolve, reject) => {
    cy.get(selector)
      .find('.data')
      .invoke('text')
      .then(text => resolve(JSON.parse(text)))
  });
}

it('form##reset', () => {
  cy.visit('/actions');
  cy.get("input[name='firstName']").type('Gob');
  cy.get("input[name='lastName']").type('Bluth');

  cy.contains('Gob');
  cy.contains('Bluth');
  cy.contains("reset").click();
  cy.contains('Gob').should('not.exist');
  cy.contains('Bluth').should('not.exist');
});

it('touch and validation', () => {
  cy.visit('/actions');

  cy.get("input[name='firstName']").type('Gob');
  cy.get("input[name='lastName']").type('Bluth');
  cy.get("input[name='firstName']").clear();
  cy.get("input[name='firstName']").blur();

  return getData('.firstNameProps')
    .then(data => {
      const meta = data.meta;
      const { active, dirty, error, invalid, modified, pristine, touched, valid, visited } = meta;
      expect(active).to.equal(false);
      expect(dirty).to.equal(true);
      expect(error).to.equal("First name can't be empty");
      expect(invalid).to.equal(true);
      expect(modified).to.equal(true);
      expect(pristine).to.equal(false);
      expect(touched).to.equal(true);
      expect(valid).to.equal(false);
      expect(visited).to.equal(true);

      return getData('.lastNameProps')
    }).then(data => {
      const meta = data.meta;
      const { active, dirty, error, invalid, modified, pristine, touched, valid, visited } = meta;
      expect(active).to.equal(false);
      expect(dirty).to.equal(true);
      expect(error).to.equal(undefined);
      expect(invalid).to.equal(false);
      expect(modified).to.equal(true);
      expect(pristine).to.equal(false);
      expect(touched).to.equal(true);
      expect(valid).to.equal(true);
      expect(visited).to.equal(true);
      
      return getData('.formProps');
    }).then(data => {
      const { valid, pristine } = data;
      expect(valid).to.equal(false);
      expect(pristine).to.equal(false);
    });
});

it('untouched', () => {
  cy.visit('/actions');
  cy.wait(100); // Let the form initialize. Possible race condition.

  return getData('.firstNameProps')
    .then(data => {
      const meta = data.meta;
      const { active, dirty, error, invalid, modified, pristine, touched, valid, visited } = meta;
      expect(active).to.equal(false);
      expect(dirty).to.equal(false);
      expect(error).to.equal("First name can't be empty");
      expect(invalid).to.equal(true);
      expect(modified).to.equal(false);
      expect(pristine).to.equal(true);
      expect(touched).to.equal(false);
      expect(valid).to.equal(false);
      expect(visited).to.equal(false);
      
      return getData('.formProps');
    }).then(data => {
      const { valid, pristine } = data;
      expect(valid).to.equal(false);
      expect(pristine).to.equal(true);
    });
});